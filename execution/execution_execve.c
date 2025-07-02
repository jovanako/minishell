/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_execve.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:16:07 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/02 21:35:51 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// input_fd - file descriptor of input stream. 0 if STDIN
// output_fd - file descriptor of output stream. 1 if STDOUT

#include <unistd.h>
#include "execution.h"

static char	*resolve_exec_path(char *relative, t_list *env_vars)
{
	// TODO implement
	(void)env_vars; // remove after impl
	return (relative);
}

static bool	child_process(t_command *cmd, t_list *ev, t_fork_streams *fork_streams)
{
	char	*path_name;

	path_name = resolve_exec_path(cmd->argv[0], ev);
	if (fork_streams->input_fd != 0)
	{
		if (dup2(fork_streams->input_fd, STDIN_FILENO) == -1)
			return (false);
		close(fork_streams->input_fd);
	}
	if (fork_streams->output_fd != 1)
	{
		if (dup2(fork_streams->output_fd, STDOUT_FILENO) == -1)
			return (false);
		close(fork_streams->output_fd);
	}
	if (execve(path_name, cmd->argv, ev_list_to_arr(ev)) == -1)
		return (false);
	return (true);
}

bool	fork_execve(t_command *cmd, t_list *ev, t_fork_streams *fork_streams)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (false);
	if (pid == 0) // child
	{
		if (!child_process(cmd, ev, fork_streams))
			return (false);
	}
	close(fork_streams->input_fd);
	close(fork_streams->output_fd);
	cmd->pid = pid;
	return (true);
}
