/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_execve.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:16:07 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/22 20:07:43 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// input_fd - file descriptor of input stream. 0 if STDIN
// output_fd - file descriptor of output stream. 1 if STDOUT

#include <unistd.h>
#include "execution.h"

static char	*resolve_exec_path(char *relative, t_list *env_vars)
{
	char	*result;

	result = ft_cmdpath(env_vars, relative);
	return (result);
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
	t_list	*env_cpy;

	pid = fork();
	if (pid == -1)
		return (false);
	if (pid == 0) // child
	{
		env_cpy = resolve_fork_ev(cmd->assignments, ev);
		if (!env_cpy)
			exit(1);
		if (!child_process(cmd, env_cpy, fork_streams))
			exit(1);
		exit(0);
	}
	if (fork_streams->input_fd != STDIN_FILENO)
		close(fork_streams->input_fd);
	if (fork_streams->output_fd != STDOUT_FILENO)
		close(fork_streams->output_fd);
	cmd->pid = pid;
	return (true);
}
