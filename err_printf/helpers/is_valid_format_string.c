/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_format_string.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:03:58 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/22 20:17:56 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../err_printf.h"

int	is_valid_format_string(char c)
{
	const char	*set;

	set = "cspdiuxX%";
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}
