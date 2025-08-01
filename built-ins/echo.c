/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:55:24 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/21 15:08:03 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

// returns 1 if s is structured "-n...n"
static int	ft_echo_option(char *s)
{
	int	i;

	i = 0;
	if (s[i++] != '-')
		return (0);
	while (s[i] == 'n')
		i++;
	if (s[i])
		return (0);
	return (1);
}

// prints all non-flag arguments to the standard output
int	ft_echo(char **tokens)
{
	int	i;
	int	n;

	if (!tokens[1])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	i = 1;
	n = 0;
	while (ft_echo_option(tokens[i]) && tokens[i])
	{
		i++;
		n = 1;
	}
	while (tokens[i])
	{
		ft_putstr_fd(tokens[i], STDOUT_FILENO);
		i++;
		if (tokens[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!n)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
