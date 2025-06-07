/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:34:55 by jkovacev          #+#    #+#             */
/*   Updated: 2024/11/21 16:41:55 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*ptr;
	int		bytes;

	bytes = nelem * elsize;
	if (nelem && bytes / nelem != elsize)
		return (0);
	ptr = malloc(bytes);
	if (!ptr)
		return (0);
	ft_memset(ptr, 0, bytes);
	return (ptr);
}
