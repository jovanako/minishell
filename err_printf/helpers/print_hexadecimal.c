/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexadecimal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:00:34 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/22 20:18:01 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../err_printf.h"

static int	count_hex_digits(unsigned int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n != 0)
	{
		n /= 16;
		count++;
	}
	return (count);
}

static char	*generate_hex_string(unsigned int n, int i, char *result)
{
	const char	*hex_digits;

	hex_digits = "0123456789abcdef";
	while (n != 0)
	{
		result[i] = hex_digits[n % 16];
		n /= 16;
		i--;
	}
	return (result);
}

char	*print_hexadecimal(unsigned int n)
{
	int		count_hex;
	char	*result;

	count_hex = count_hex_digits(n);
	result = (char *)malloc((count_hex + 1) * sizeof(char));
	if (result == NULL)
		return (0);
	result[count_hex] = '\0';
	if (n == 0)
	{
		result[0] = '0';
		return (result);
	}
	count_hex--;
	result = generate_hex_string(n, count_hex, result);
	return (result);
}
