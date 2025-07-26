/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:55:42 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/26 19:49:35 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

//	exit (0)	= e + "exit"
//	exit  x ( )	= e + "exit" + "minishell: exit: aa: numeric argument required"
//	exit  0  x	= e + "exit" + "minishell: exit: too many arguments"
int	ft_exit(t_exec_ctx *ctx, char *argv[])
{
	int	exit_code;

	printf("exit\n");
	if (!argv[1])
		exit_code = 0;
	else if (!ft_isnumber(argv[1]))
		printf("minishell: exit: aa: numeric argument required\n");
	else if (argv[2])
		printf("minishell: exit: too many arguments\n");
	else
		exit_code = ft_atoi(argv[1]);
	ctx->exit = true;
	return (exit_code);
}

int	ft_exit_shell(int exit_code)
{
	exit(exit_code);
	return (1);
}
