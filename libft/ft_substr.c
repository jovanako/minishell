/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:08:13 by jkovacev          #+#    #+#             */
/*   Updated: 2024/11/18 12:53:19 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calculate_substring_size(size_t start_index,
		size_t src_length, size_t max_len)
{
	if (start_index < src_length)
	{
		if (max_len <= (src_length - start_index))
		{
			return (max_len);
		}
		return (src_length - start_index);
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;
	size_t	s_len;
	size_t	substring_size;

	s_len = ft_strlen(s);
	substring_size = calculate_substring_size(start, s_len, len);
	substr = (char *) malloc (substring_size * sizeof(char) + 1);
	if (!substr)
		return (0);
	i = 0;
	j = start;
	while ((j < s_len) && (j < (start + len)))
	{
		substr[i] = s[j];
		i++;
		j++;
	}
	substr[i] = '\0';
	return (substr);
}
