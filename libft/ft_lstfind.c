/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:15:47 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/20 10:23:59 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstfind(t_list *lst, bool (*f)(void *, void *), void *f_arg)
{
	t_list	*current;

	current = lst;
	while (current)
	{
		if (f(current->content, f_arg))
			return (current->content);
		current = current->next;
	}
	return (NULL);
}
