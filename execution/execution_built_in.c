/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_built_in.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:21:54 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/10 20:24:28 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../utils/utils.h"
#include "../built-ins/built_ins.h"

int	exec_built_in(t_execution_context *ctx, char *av[], t_list *ev)
{
	t_built_in_name	built_in;

	built_in = find_built_in_name(av[0]);
	if (built_in == ECHO)
		return (ft_echo(av));
	if (built_in == CD)
		return (ft_cd(av[1], ev)); // check if av[1] exists
	if (built_in == PWD)
		return (ft_pwd());
	if (built_in == EXPORT) 
	 	return (ft_export(av, ev));
	if (built_in == UNSET) 
		return (ft_unset(av, ev));
	if (built_in == ENV)
		return (ft_env(ev));
	if (built_in == EXIT)
	 	return (ft_exit(ctx, av)); // handle as a signal
	return (0); // TODO fix
}

bool	is_built_in(char *cmd_name)
{
	return (is_str_equal(cmd_name, "echo")
		|| is_str_equal(cmd_name, "cd")
		|| is_str_equal(cmd_name, "pwd")
		|| is_str_equal(cmd_name, "export")
		|| is_str_equal(cmd_name, "unset")
		|| is_str_equal(cmd_name, "env")
		|| is_str_equal(cmd_name, "exit"));		
}

bool	is_special_built_in(t_list *commands)
{
	char	*cmd_name;
	
	if (ft_lstsize(commands) != 1)
		return (false);
	cmd_name = ((t_command *)commands->content)->argv[0];
	return (is_str_equal(cmd_name, "export")
			|| is_str_equal(cmd_name, "unset")
			|| is_str_equal(cmd_name, "exit")
			|| is_str_equal(cmd_name, "cd"));
}

t_built_in_name	find_built_in_name(char *cmd_name)
{
	if (is_str_equal(cmd_name, "echo"))
		return (ECHO);
	if (is_str_equal(cmd_name, "cd"))
		return (CD);
	if (is_str_equal(cmd_name, "pwd"))
		return (PWD);
	if (is_str_equal(cmd_name, "export"))
		return (EXPORT);
	if (is_str_equal(cmd_name, "unset"))
		return (UNSET);
	if (is_str_equal(cmd_name, "env"))
		return (ENV);
	if (is_str_equal(cmd_name, "exit"))
		return (EXIT);
	return (INVALID);
}

bool	fork_built_in(t_execution_context *ctx, t_command *command, t_list *ev, t_fork_streams *s)
{
	pid_t			pid;

	pid = fork();
	if (pid == -1)
		return (false);
	if (pid == 0) // child
	{
		if (s->input_fd != 0)
		{
			if (dup2(s->input_fd, STDIN_FILENO) == -1)
				return (false);
			close(s->input_fd);
		}
		if (s->output_fd != 1)
		{
			if (dup2(s->output_fd, STDOUT_FILENO) == -1)
				return (false);
			close(s->output_fd);
		}
		exit (exec_built_in(ctx, command->argv, ev));
	}
	if (s->input_fd != STDIN_FILENO)
		close(s->input_fd);
	if (s->output_fd != STDOUT_FILENO)
		close(s->output_fd);
	command->pid = pid;
	return (true);
}
