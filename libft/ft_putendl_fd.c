/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:16:05 by jkovacev          #+#    #+#             */
/*   Updated: 2024/11/28 15:16:10 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (*ptr != '\0')
	{
		write (fd, ptr, 1);
		ptr++;
	}
	write (fd, "\n", 1);
}
