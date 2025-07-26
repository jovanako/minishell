/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_built_in.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:21:54 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/26 19:49:35 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../utils/utils.h"
#include "../built-ins/built_ins.h"

int	exec_built_in(t_exec_ctx *ctx, t_command *cmd)
{
	char	**argv;
	
	argv = cmd->argv;
	if (is_str_equal(argv[0], "echo"))
		return (ft_echo(argv));
	if (is_str_equal(argv[0], "cd"))
		return (ft_cd(argv[1], ctx->env_vars)); // check if argv[1] exists
	if (is_str_equal(argv[0], "pwd"))
		return (ft_pwd());
	if (is_str_equal(argv[0], "export")) 
	 	return (ft_export(argv, ctx->env_vars, cmd->assignments));
	if (is_str_equal(argv[0], "unset")) 
		return (ft_unset(argv, ctx->env_vars, cmd->assignments));
	if (is_str_equal(argv[0],"env"))
		return (ft_env(ctx->env_vars));
	if (is_str_equal(argv[0], "exit"))
	 	return (ft_exit(ctx, argv)); // handle as a signal
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

bool	fork_built_in(t_exec_ctx *ctx, t_command *command, t_fork_streams *s)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (false);
	if (pid == 0) // child
	{
		if (s->input_fd != 0)
		{
			if (dup2(s->input_fd, STDIN_FILENO) == -1)
				exit(1);
			close(s->input_fd);
		}
		if (s->output_fd != 1)
		{
			if (dup2(s->output_fd, STDOUT_FILENO) == -1)
				exit(1);
			close(s->output_fd);
		}
		ctx->env_vars = resolve_fork_ev(command->assignments, ctx->env_vars);
		if (!ctx->env_vars)
			exit(1);
		exit(exec_built_in(ctx, command));
	}
	if (s->input_fd != STDIN_FILENO)
		close(s->input_fd);
	if (s->output_fd != STDOUT_FILENO)
		close(s->output_fd);
	command->pid = pid;
	return (true);
}
