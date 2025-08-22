/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_printf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:15:59 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/22 20:20:18 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "err_printf.h"

static int	argument_to_print(const char *format, va_list args)
{
	int	count;

	count = 0;
	if (*format == 'c')
		count += print_char(va_arg(args, int));
	else if (*format == 's')
		count += print_string(va_arg(args, char *));
	else if (*format == 'p')
		count += print_pointer(va_arg(args, void *));
	else if (*format == 'd' || *format == 'i')
		count += print_int(va_arg(args, int));
	else if (*format == 'u')
		count += print_unsigned(va_arg(args, int));
	else if (*format == 'x')
		count += print_hex_low(va_arg(args, int));
	else if (*format == 'X')
		count += print_hex_up(va_arg(args, int));
	else if (*format == '%')
		count += print_char('%');
	return (count);
}

int	err_printf(const char *format, ...)
{
	int		count;
	va_list	args;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%' && is_valid_format_string(*(format + 1)) == 1)
		{
			format++;
			count += argument_to_print(format, args);
		}
		else
		{
			if (write (STDERR_FILENO, format, 1) == -1)
				return (-1);
			count++;
		}
		format++;
	}
	va_end(args);
	return (count);
}
