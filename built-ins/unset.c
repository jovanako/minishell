/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:56:08 by culbrich          #+#    #+#             */
/*   Updated: 2025/08/23 10:08:58 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static void	ft_lstdelfill_loop(t_list *to_del, t_list *curr)
{
	while (curr && to_del)
	{
		if (curr->next == to_del)
		{
			if (curr->next->next)
				curr->next = curr->next->next;
			else
				curr->next = NULL;
			ft_lstdelone(to_del, delete_env_var);
		}
		curr = curr->next;
	}
}

static void	ft_lstdelfill(t_list **start, t_list *to_del)
{
	t_list	*curr;

	curr = *start;
	if (to_del)
	{
		if (curr == to_del)
		{
			if (curr->next)
				*start = curr->next;
			ft_lstdelone(to_del, delete_env_var);
		}
		else
			ft_lstdelfill_loop(to_del, curr);
	}
}

int	ft_unset(char **keys, t_list **env_vars, t_list *assignments)
{
	int		i;

	i = 1;
	while (keys[i])
	{
		if (!ft_lstfind(assignments, &match_assignment_key, keys[i]))
			ft_lstdelfill(env_vars, ft_getenv(*env_vars, keys[i]));
		i++;
	}
	return (0);
}
