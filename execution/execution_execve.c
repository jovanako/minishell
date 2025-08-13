/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_execve.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:16:07 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/29 18:33:09 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// input_fd - file descriptor of input stream. 0 if STDIN
// output_fd - file descriptor of output stream. 1 if STDOUT

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "execution.h"

static char	*contains_path(char *arg)
{
	if (access(arg, F_OK) == -1 || access(arg, X_OK) == -1)
	{
		printf("minishell: %s: %s\n", arg, strerror(errno));
		return (NULL);
	}
	return (arg);
}

static char	*resolve_exec_path(char *arg, t_list *env_vars)
{
	char	*result;

	if (ft_strchr(arg, '/'))
		result = contains_path(arg);
	else
	{
		result = ft_cmdpath(env_vars, arg);
		if (!result)
		{
			printf("minishell: %s: command not found\n", arg);
			return (NULL);
		}
		if (access(result, X_OK) == -1)
		{
			printf("minishell: %s: %s\n", arg, strerror(errno));
			return (NULL);
		}
	}
	return (result);
}

static int	child_process(t_command *cmd, t_list *ev,
	t_fork_streams *fork_streams)
{
	char	*path_name;

	path_name = resolve_exec_path(cmd->argv[0], ev);
	if (!path_name)
		return (127);
	if (fork_streams->input_fd != 0)
	{
		if (dup2(fork_streams->input_fd, STDIN_FILENO) == -1)
			return (1);
		close(fork_streams->input_fd);
	}
	if (fork_streams->output_fd != 1)
	{
		if (dup2(fork_streams->output_fd, STDOUT_FILENO) == -1)
			return (1);
		close(fork_streams->output_fd);
	}
	if (execve(path_name, cmd->argv, ev_list_to_arr(ev)) == -1)
		return (1);
	return (0);
}

//	pid 0 = child
bool	fork_execve(t_command *cmd, t_list *ev, t_fork_streams *fork_streams)
{
	pid_t	pid;
	t_list	*env_cpy;

	pid = fork();
	if (pid == -1)
		return (false);
	if (pid == 0)
	{
		env_cpy = resolve_fork_ev(cmd->assignments, ev);
		if (!env_cpy)
			exit(1);
		exit(child_process(cmd, env_cpy, fork_streams));
	}
	if (fork_streams->input_fd != STDIN_FILENO)
		close(fork_streams->input_fd);
	if (fork_streams->output_fd != STDOUT_FILENO)
		close(fork_streams->output_fd);
	cmd->pid = pid;
	return (true);
}
