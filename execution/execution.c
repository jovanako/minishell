/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:22:28 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/29 20:43:37 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	wait_for_children(t_list *commands)
{
	t_command	*cmd;
	int			status;

	while (commands)
	{
		cmd = commands->content;
		waitpid(cmd->pid, &status, 0);
		commands = commands->next;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static bool	execute_fork(t_exec_ctx *ctx, t_command *cmd, t_fork_streams *fs)
{
	if (!ctx->env_vars)
		return (false);
	if (is_built_in(cmd->argv[0]))
		fork_built_in(ctx, cmd, fs);
	else
		fork_execve(cmd, ctx->env_vars, fs);
	return (true);
}

static bool	add_redirs(t_fork_streams *fs, t_list *redirs, t_exec_ctx *ctx)
{
	t_redirection	*current_redir;

	while (redirs)
	{
		current_redir = (t_redirection *)redirs->content;
		if (current_redir->type == INPUT_REDIRECT
			&& open_input_redir(fs, current_redir) == -1)
			return (true);
		else if (current_redir->type == OUTPUT_REDIRECT
			&& open_output_redir(fs, current_redir) == -1)
			return (true);
		else if (current_redir->type == APPEND_REDIRECT
			&& open_append_redir(fs, current_redir) == -1)
			return (true);
		else if (current_redir->type == HEREDOC_REDIRECT
			&& open_hd_redir(fs, current_redir, ctx) == -1)
			return (true);
		redirs = redirs->next;
	}
	return (false);
}

static bool	execute_command_helper(int *fd, t_fork_streams *fork_streams, t_exec_ctx *ctx, t_command *command)
{
	if (ctx->commands->next)
	{
		if (pipe(fd) == -1)
			return (false);
		fork_streams->output_fd = fd[1];
	}
	ctx->error = add_redirs(fork_streams, command->redirections, ctx);
	if (ctx->error)
		return (true);
	if (!execute_fork(ctx, command, fork_streams))
		return (false);
	return (true);
}

// last input and output redirections win
// input redirection takes precedence over input_fd
// read end: 0 write end: 1
static bool	execute_command(t_exec_ctx *ctx, int input_fd)
{
	int				fd[2];
	t_command		*command;
	t_fork_streams	*fork_streams;

	command = ctx->commands->content;
	fork_streams = malloc(sizeof(t_fork_streams));
	if (!fork_streams)
		return (false);
	fork_streams->input_fd = input_fd;
	fork_streams->output_fd = STDOUT_FILENO;
	execute_command_helper(fd, fork_streams, ctx, command);
	if (ctx->commands->next)
	{
		ctx->commands = ctx->commands->next;
		execute_command(ctx, fd[0]);
	}
	free(fork_streams);
	return (true);
}

t_exec_ctx	*execute(t_parse_ctx *p_ctx, t_list *env_vars, int status)
{
	t_exec_ctx	*ctx;
	t_command	*cmd;

	if (!p_ctx)
		return (NULL);
	ctx = new_exec_ctx(p_ctx, env_vars, status);
	if (!ctx)
		return (NULL);
	if (!ctx->commands)
		return (NULL);
	cmd = ctx->commands->content;
	if (!cmd->argv[0])
		ctx->status = handle_no_command(cmd, ctx->env_vars);
	else if (is_special_built_in(ctx->commands))
		ctx->status = exec_built_in(ctx, cmd);
	else
	{
		if (!execute_command(ctx, 0))
			return (NULL);
		ctx->status = wait_for_children(ctx->commands);
	}
	return (ctx);
}
