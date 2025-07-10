/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:55:42 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/10 19:20:52 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

//	TODO:
//	exit (0)	= e + "exit"
//	exit  x 	= e + "exit" + "minishell: exit: aa: numeric argument required"
//	exit  0 x	= e + "exit" + "minishell: exit: too many arguments"
int	ft_exit(t_execution_context *ctx, char *argv[])
{
	if (argv[1] && argv[2])
	{
		printf("minishell: exit: too many arguments");
		return (1);
	}
	else
	if (!argv[1] || (argv[1] && ft_isnumber(argv[1])))
	{
		printf("exit\n");
		ctx->exit = true;
	}
	return (1);
}

int	ft_exit_shell(t_list **env_vars, int exit_code)
{
	ft_lstclear(env_vars, &delete_env_var);
	exit(exit_code);
	return (1);
}
