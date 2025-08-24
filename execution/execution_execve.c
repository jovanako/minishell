/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_execve.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:16:07 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/24 16:09:46 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// input_fd - file descriptor of input stream. 0 if STDIN
// output_fd - file descriptor of output stream. 1 if STDOUT

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "execution.h"
#include "../err_printf/err_printf.h"

static char	*contains_path(char *arg)
{
	if (access(arg, F_OK) == -1 || access(arg, X_OK) == -1)
	{
		err_printf("minishell: %s: %s\n", arg, strerror(errno));
		return (NULL);
	}
	if (is_dir(arg))
	{
		err_printf("minishell: %s: Is a directory\n", arg);
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
			err_printf("minishell: %s: command not found\n", arg);
			return (NULL);
		}
		if (access(result, X_OK) == -1)
		{
			err_printf("minishell: %s: %s\n", arg, strerror(errno));
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
	{
		if (errno == EACCES || is_dir(cmd->argv[0]))
			return (126);
		return (127);
	}
	if (fork_streams->input_fd != STDIN_FILENO)
	{
		if (dup2(fork_streams->input_fd, STDIN_FILENO) == -1)
			return (1);
		close(fork_streams->input_fd);
	}
	if (fork_streams->output_fd != STDOUT_FILENO)
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
bool	fork_execve(t_command *cmd, t_list **ev, t_fork_streams *fork_streams)
{
	pid_t	pid;
	t_list	**env_cpy;

	pid = fork();
	if (pid == -1)
		return (false);
	if (pid == 0)
	{
		if (fork_streams->input_fd != fork_streams->pipe_in)
			close(fork_streams->pipe_in);
		if (fork_streams->output_fd != fork_streams->pipe_out)
			close(fork_streams->pipe_out);
		env_cpy = resolve_fork_ev(cmd->assignments, ev);
		if (!(*env_cpy))
			exit(1);
		exit(child_process(cmd, *env_cpy, fork_streams));
	}
	if (fork_streams->input_fd != STDIN_FILENO)
		close(fork_streams->input_fd);
	if (fork_streams->output_fd != STDOUT_FILENO)
		close(fork_streams->output_fd);
	cmd->pid = pid;
	return (true);
}
