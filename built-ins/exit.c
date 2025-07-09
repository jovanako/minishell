/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: culbrich <culbrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:55:42 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/03 15:38:46 by culbrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

//	TODO:
//	exit (0)	= e + "exit"
//	exit  x 	= e + "exit" + "minishell: exit: aa: numeric argument required"
//	exit  0 x	= e + "exit" + "minishell: exit: too many arguments"
int	ft_exit(char **tokens)
{
	if (tokens[1] && tokens[2])
	{
		printf("minishell: exit: too many arguments");
		return (1);
	}
	else
	if (!tokens[1] || (tokens[1] && ft_isnumber(tokens[1])))
		printf("exit\n");
	return (1);
}

int	ft_exit_shell(t_list **env_vars, int exit_code)
{
	ft_lstclear(env_vars, &delete_env_var);
	exit(exit_code);
	return (1);
}
