/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:00:56 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/22 20:17:36 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../err_printf.h"

static int	count_hex_digits(unsigned long n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n > 0)
	{
		n /= 16;
		count++;
	}
	return (count);
}

static char	*generate_hex_string(unsigned long n, int i, char *result)
{
	const char	*hex_digits;

	hex_digits = "0123456789abcdef";
	while (n > 0)
	{
		result[i] = hex_digits[n % 16];
		n /= 16;
		i--;
	}
	return (result);
}

int	print_pointer(void *p)
{
	unsigned long	address_decimal;
	int				count_hex;
	int				count;
	char			*result;

	if (p == NULL)
		return (ft_putstr("(nil)"));
	address_decimal = (unsigned long)p;
	count_hex = count_hex_digits(address_decimal) + 2;
	result = (char *)malloc((count_hex + 1) * sizeof(char));
	if (result == NULL)
		return (0);
	result[count_hex] = '\0';
	result[0] = '0';
	result[1] = 'x';
	count_hex--;
	result = generate_hex_string(address_decimal, count_hex, result);
	count = write_str(result);
	return (count);
}
