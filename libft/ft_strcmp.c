/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: culbrich <culbrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:12:19 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/03 15:16:45 by culbrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int				diff;
	unsigned int	i;
	unsigned char	*s1_t;
	unsigned char	*s2_t;

	diff = 0;
	i = 0;
	s1_t = (unsigned char *)s1;
	s2_t = (unsigned char *)s2;
	while (s1[i] && s2[i])
	{
		diff = s1_t[i] - s2_t[i];
		if (diff != 0)
			return (diff);
		i++;
	}
	if (s1[i] && !s2[i])
		diff = s1_t[i];
	else if (!s1[i] && s2[i])
		diff = -s2_t[i];
	return (diff);
}
