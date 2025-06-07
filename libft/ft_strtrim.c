/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:33:50 by jkovacev          #+#    #+#             */
/*   Updated: 2024/11/22 16:17:22 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	is_equal(char c, char const *set)
{
	unsigned int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*generate_trimmed_copy(char const *s1,
		char *copy, size_t start, size_t copy_size)
{
	size_t	i;

	i = 0;
	while (i < copy_size)
	{
		copy[i] = s1[start];
		i++;
		start++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*copy;
	size_t	end;
	size_t	s1_len;
	size_t	start;
	size_t	copy_size;

	if (!s1)
		return (0);
	s1_len = ft_strlen(s1);
	start = 0;
	end = s1_len - 1;
	while (s1[start] && is_equal(s1[start], set))
	{
		start++;
	}
	while ((end > start) && is_equal(s1[end], set))
	{
		end--;
	}
	copy_size = end - start + 1;
	copy = (char *) malloc (copy_size * sizeof(char) + 1);
	if (!copy)
		return ((char *)0);
	return (generate_trimmed_copy(s1, copy, start, copy_size));
}
