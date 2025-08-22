/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_printf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:45:27 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/22 20:20:30 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_PRINTF_H
# define ERR_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int		write_str(char *s);
char	*print_hexadecimal(unsigned int n);
int		ft_putstr(char *s);
int		is_valid_format_string(char c);
int		err_printf(const char *format, ...);
int		print_char(char c);
int		print_string(char *str);
int		print_pointer(void *p);
int		print_int(int n);
int		print_unsigned(int n);
int		print_hex_low(int n);
int		print_hex_up(int n);

#endif
