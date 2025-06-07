/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:19:05 by jkovacev          #+#    #+#             */
/*   Updated: 2024/11/20 15:50:36 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*p_first;
	size_t	i;
	size_t	little_len;

	i = 0;
	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	if (*big && (len < little_len))
		return (NULL);
	if (len)
	{
		while (big[i] && (i <= (len - little_len)))
		{
			p_first = (char *)&big[i];
			if (ft_strncmp(p_first, little, little_len) == 0)
				return (p_first);
			i++;
		}
	}
	return (NULL);
}
