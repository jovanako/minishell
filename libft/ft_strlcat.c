/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:49:59 by jkovacev          #+#    #+#             */
/*   Updated: 2024/11/28 15:15:20 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*d;
	char	*s;
	size_t	dstlen;
	size_t	bytes_left;

	d = (char *)dst;
	s = (char *)src;
	bytes_left = dstsize;
	while (bytes_left-- != 0 && *d != '\0')
		d++;
	dstlen = d - dst;
	if (dstlen == dstsize)
		return (dstlen + ft_strlen(src));
	bytes_left = dstsize - dstlen;
	while (*s != '\0')
	{
		if (bytes_left != 1)
		{
			*d++ = *s;
			bytes_left--;
		}
		s++;
	}
	*d = '\0';
	return (dstlen + (s - src));
}
