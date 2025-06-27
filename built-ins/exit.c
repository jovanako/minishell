/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: culbrich <culbrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:55:42 by culbrich          #+#    #+#             */
/*   Updated: 2025/06/27 14:18:07 by culbrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

void	ft_exit(t_list **lst, int exit_code)
{
	// save all minishell data in a struct to cleanly free?
	if (lst)
		ft_lstclear(lst, delete_env_var);
	exit(exit_code);
}

/*	Exit code Conventions:
 *	0	- Success
 * 	1	- General Error
 * 	2	- Misuse of built-ins
 * 	126	- Invoked command failed to execute
 * 	127	- Command not fund
 * 	128	- Invalid exit argument
 * 	130	- Termination by ctrl-c
 * 	255	- Exit status out of range/custom fatal error
 * 
 * 	129-255	- Exit via signal (128 + signum)
*/
