/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:28:38 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/04 14:33:18 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_vars.h"

bool	add_env_var(t_list *env_vars, char *key, char *val, bool exported)
{
	t_env_var	*new_var;
	t_list		*node;
	
	new_var = malloc(sizeof(t_env_var));
	if (!new_var)
		return (false);
	new_var->exported = exported;
	new_var->key = key;
	new_var->value = val;
	node = ft_lstnew(new_var);
	if (!node)
	{
		free(new_var);
		return (false);
	}
	ft_lstadd_back(&env_vars, node);
	return (true);
}
