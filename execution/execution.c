/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:22:28 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/07 19:31:41 by jkovacev         ###   ########.fr       */
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

static void	execute_fork(t_command *command, t_fork_streams *fs, t_list *env_vars)
{
	t_list	*assignments;
	
	assignments = resolve_assignments(command->assignments, env_vars);
	if (is_built_in(command->argv[0]))
	{
		fork_built_in(command, assignments, fs);
	}
	else
		fork_execve(command, env_vars, fs);	
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
		current_node = current_node->next;
	}
	return (true);
}

// last input and output redirections win
// input redirection takes precedence over input_fd
static bool	execute_command(t_list* commands, t_list* env_vars, int input_fd)
{
	int				fd[2]; // read end: 0 write end: 1
	t_command		*command;
	t_fork_streams	*fork_streams;

	command = commands->content;
	fork_streams = malloc(sizeof(t_fork_streams));
	if (!fork_streams)
		return (false);
	fork_streams->input_fd = input_fd;
	fork_streams->output_fd = STDOUT_FILENO;
	if (commands->next)
	{
		if (pipe(fd) == -1)
			return (false);
		fork_streams->output_fd = fd[1];
	}
	if (!add_redirs(fork_streams, command->redirections))
		return (false);
	execute_fork(command, fork_streams, env_vars);
	if (commands->next)
	{
		// use read end as input for the next command
		execute_command(commands->next, env_vars, fd[0]);
		close(fd[1]);
		close(fd[0]);
	}
	free(fork_streams);
	return (true);
}

bool	execute(t_list* commands, t_list* env_vars)
{
	t_command 	*cmd;
	int			status;

	if (!commands)
		return (true);	
	cmd = commands->content;
	if (!cmd->argv[0])
		status = handle_no_command(cmd, env_vars);
	else if (is_special_built_in(commands))
	{
		// do assignments and redirects
		status = exec_built_in(find_built_in_name(cmd->argv[0]), cmd->argv, env_vars);
	}
	else
	{
		execute_command(commands, env_vars, 0);
		status = wait_for_children(commands);
	}
	(void)status;
	return (true); // TODO return status
}
