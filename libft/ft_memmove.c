/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:06:22 by jkovacev          #+#    #+#             */
/*   Updated: 2024/11/20 10:55:21 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy_from_src_to_dest(char *d,
		const char *s, size_t size)
{
	size_t	i;

	if ((d > s) && (d < (s + size)))
	{
		i = size - 1;
		while (size != 0)
		{
			d[i] = s[i];
			size--;
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < size)
		{
			d[i] = s[i];
			i++;
		}
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		size;

	if (dest == NULL && src == NULL)
		return (dest);
	d = dest;
	s = src;
	size = n;
	copy_from_src_to_dest(d, s, size);
	return (dest);
}
