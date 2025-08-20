/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: culbrich <culbrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:55:42 by culbrich          #+#    #+#             */
/*   Updated: 2025/08/20 18:02:36 by culbrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static long int	ft_exit_atoi(char *arg, int i)
{
	long int	result;

	result = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (-1);
		result = result * 10 + (arg[i] - '0');
		i++;
	}
	return (result);
}

static int ft_valid_exit_code(char *arg)
{
	int			i;
	int			sign;
	long int	result;

	i = 0;
	sign = 1;
	if (arg[0] == '+' || arg[0] == '-')
	{
		if (arg[0] == '-')
			sign = -1;
		i++;
	}
	result = ft_exit_atoi(arg, i);
	if (result == -1)
		return (-1);
	result *= sign;
	if (result < INT_MIN || result > INT_MAX)
		return (-1);
	return ((int)(result % 256));
}

//	exit (0)	= e + "exit"
//	exit  x ( )	= e + "exit" + "minishell: exit: []: numeric argument required"
//	exit  0  x	= e + "exit" + "minishell: exit: too many arguments"
int	ft_exit(t_exec_ctx *ctx, char *argv[])
{
	int	exit_code;

	ctx->exit = true;
	printf("exit\n");
	if (!argv[1])
		return (0);
	exit_code = ft_valid_exit_code(argv[1]);
	if (exit_code == -1)
	{
		ft_putendl_fd("minishell: exit: numeric argument required",
			STDERR_FILENO);
		return (2);
	}
	else if (argv[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		ctx->exit = false;
		return (1);
	}
	return (exit_code);
}

bool	ft_exit_sigeof(void)
{
	printf("exit\n");
	return (true);
}
