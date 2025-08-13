/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:28:38 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/26 22:42:09 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_vars.h"

static bool	update_var(t_env_var *env_var, char *val, bool exported)
{
	env_var->exported = exported;
	env_var->value = val;
	return (true);
}

static bool	add_new_var(t_list **env_vars, char *key, char *val, bool exported)
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
	ft_lstadd_back(env_vars, node);
	return (true);
}

bool	add_env_var(t_list **env_vars, char *key, char *val, bool exported)
{
	t_env_var	*existing_env_var;

	existing_env_var = get_env_var(*env_vars, key);
	if (existing_env_var)
	{
		if (val == NULL)
			val = existing_env_var->value;
		return (update_var(existing_env_var, val, exported));
	}
	return (add_new_var(env_vars, key, val, exported));
}
