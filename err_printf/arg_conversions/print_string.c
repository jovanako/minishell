/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:05:29 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/22 20:17:41 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../err_printf.h"

int	print_string(char *str)
{
	char	*s_nil;

	s_nil = "(null)";
	if (str == NULL)
		return (ft_putstr(s_nil));
	else
		return (ft_putstr(str));
}
