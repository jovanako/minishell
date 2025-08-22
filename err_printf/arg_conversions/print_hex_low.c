/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_low.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:03:28 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/22 20:17:18 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../err_printf.h"

static char	*to_lower(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
		{
			s[i] += 32;
		}
		i++;
	}
	return (s);
}

int	print_hex_low(int n)
{
	int		count;
	char	*result;

	result = to_lower(print_hexadecimal((unsigned int)n));
	count = write_str(result);
	return (count);
}
