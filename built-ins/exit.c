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

int	g_exit_code;

// updates exit code and returns it (flag checked in main loop)
int	ft_exit(int exit_code)
{
	g_exit_code = exit_code;
	return (exit_code);
}
