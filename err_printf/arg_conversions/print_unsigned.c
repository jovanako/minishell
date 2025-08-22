/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:02:05 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/22 20:17:47 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../err_printf.h"

static int	calculate_int_length(unsigned int n)
{
	int	int_len;

	int_len = 0;
	if (n == 0)
		int_len = 1;
	while (n > 0)
	{
		n /= 10;
		int_len++;
	}
	return (int_len);
}

static char	*generate_string(char *result, unsigned int n, int int_len)
{
	while ((int_len >= 0) && n)
	{
		result[int_len] = (n % 10) + '0';
		n /= 10;
		int_len--;
	}
	return (result);
}

int	print_unsigned(int n)
{
	int		int_len;
	int		count;
	char	*result;

	n = (unsigned int)n;
	int_len = calculate_int_length(n);
	result = (char *)malloc(int_len * (sizeof(char) + 1));
	if (!result)
		return (0);
	result[int_len] = '\0';
	if (n == 0)
	{
		result[0] = '0';
		count = write_str(result);
		return (count);
	}
	result = generate_string(result, n, int_len - 1);
	count = write_str(result);
	return (count);
}
