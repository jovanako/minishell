/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:22:28 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/20 18:54:28 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	wait_for_children(t_list *commands)
{
	t_command	*cmd;
	int			exit_status;
	
	while (commands)
	{
		cmd = commands->content;
		waitpid(cmd->pid, &exit_status, 0);
		commands = commands->next;
	}
	return (exit_status);
}

static bool	execute_fork(t_execution_context *ctx, t_command *command, t_fork_streams *fs)
{
	if (!ctx->env_vars)
		return (false);
	if (is_built_in(command->argv[0]))
	{
		fork_built_in(ctx, command, fs);
	}
	else
		fork_execve(command, ctx->env_vars, fs);
	return (true);
}

static bool	add_redirs(t_fork_streams *fork_streams, t_list *redirections)
{
	t_list			*current_node;
	t_redirection	*current_redir;

	current_node = redirections;
	while (current_node)
	{
		current_redir = (t_redirection *)current_node->content;
		if (current_redir->type == INPUT_REDIRECT)
		{
			if (open_input_redir(fork_streams, current_redir) == -1)
				return (false); // error: open failed
		}
		else if (current_redir->type == OUTPUT_REDIRECT)
		{
			if (open_output_redir(fork_streams, current_redir) == -1)
				return (false); // error: open failed
		}
		else if (current_redir->type == APPEND_REDIRECT)
		{
			if (open_append_redir(fork_streams, current_redir) == -1)
				return (false); // error: open failed
		}

		else if (current_redir->type == HEREDOC_REDIRECT)
		{
			// open temporary file for writing
			// accept user input and write it to the temp file until the input is the delimiter
			// close temp file and open it for reading
			// assign the file descriptor of the temp file open for reading to fork_streams->input_fd
		}
		current_node = current_node->next;
	}
	return (true);
}

// last input and output redirections win
// input redirection takes precedence over input_fd
static bool	execute_command(t_execution_context *ctx, int input_fd)
{
	int				fd[2]; // read end: 0 write end: 1
	t_command		*command;
	t_fork_streams	*fork_streams;

	command = ctx->commands->content;
	fork_streams = malloc(sizeof(t_fork_streams));
	if (!fork_streams)
		return (false);
	fork_streams->input_fd = input_fd;
	fork_streams->output_fd = STDOUT_FILENO;
	if (ctx->commands->next)
	{
		if (pipe(fd) == -1)
			return (false);
		fork_streams->output_fd = fd[1];
	}
	if (!add_redirs(fork_streams, command->redirections))
		return (false);
	if (!execute_fork(ctx, command, fork_streams))
		return (false);
	if (ctx->commands->next)
	{
		ctx->commands = ctx->commands->next;
		execute_command(ctx, fd[0]); 
	}
	free(fork_streams);
	return (true);
}

bool	execute(t_execution_context *ctx)
{
	t_command 	*cmd;
	
	if (!ctx->commands)
		return (true);	
	cmd = ctx->commands->content;
	if (!cmd->argv[0])
		ctx->status = handle_no_command(cmd, ctx->env_vars);
	else if (is_special_built_in(ctx->commands))
		ctx->status = exec_built_in(ctx, cmd);
	else
	{
		if (!execute_command(ctx, 0))
			return (false);
		ctx->status = wait_for_children(ctx->commands);
	}
	return (true);
}
