/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:47:37 by jkovacev          #+#    #+#             */
/*   Updated: 2024/11/22 11:15:59 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*copy_string(char *dst, const char *src, size_t size)
{
	int	i;

	i = 0;
	if (size == ft_strlen(src))
	{
		while (size > 0 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
			size--;
		}
		dst[i] = '\0';
	}
	return (dst);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	s_len;

	s_len = ft_strlen(s);
	dup = (char *)malloc(s_len * sizeof(char) + 1);
	if (dup)
	{
		dup = copy_string(dup, s, s_len);
		return (dup);
	}
	return ((void *)0);
}
