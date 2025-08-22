/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_putstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:02:37 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/22 20:21:39 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../err_printf.h"

int	ft_putstr(char *s)
{
	int		count;

	count = 0;
	while (s[count])
	{
		if (write (STDERR_FILENO, &s[count], 1) == -1)
			return (-1);
		count++;
	}
	return (count);
}
