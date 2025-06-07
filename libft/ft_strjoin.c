/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:06:46 by jkovacev          #+#    #+#             */
/*   Updated: 2024/11/12 16:12:39 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;
	size_t	len;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	result = (char *) malloc (len * sizeof(char) + 1);
	if (result)
	{
		j = 0;
		while (s1[j] != '\0')
		{
			result[i++] = s1[j++];
		}
		j = 0;
		while (s2[j] != '\0')
		{
			result[i++] = s2[j++];
		}
		result[i] = '\0';
		return (result);
	}
	return ((void *)0);
}
