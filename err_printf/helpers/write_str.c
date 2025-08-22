/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:02:29 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/22 20:20:55 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../err_printf.h"

int	write_str(char *s)
{
	int	count;

	count = 0;
	while (s[count] != '\0')
	{
		if (write (STDERR_FILENO, &s[count], 1) == -1)
		{
			free(s);
			return (-1);
		}
		count++;
	}
	free(s);
	return (count);
}
