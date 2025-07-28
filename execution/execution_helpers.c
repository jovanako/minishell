/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:32:00 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/28 19:28:57 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>
#include <string.h>

static bool	resolve_assignments(t_list *assignments, t_list **copy)
{
	t_assignment	*assignment;
	char			*key;
	char			*value;

	while (assignments)
	{
		assignment = assignments->content;
		key = ft_strcpy(assignment->key);
		if (!key)
			return (false);
		value = ft_strcpy(assignment->value);
		if (!value)
			return (false);
		if (!add_env_var(copy, key, value, true))
			return (false);
		assignments = assignments->next;
	}
	return (true);
}

static bool	resolve_ev(t_list **env_vars, t_list **copy)
{
	t_env_var		*env_var;
	char			*key;
	char			*value;

	while (*env_vars)
	{
		env_var = (*env_vars)->content;
		if (env_var->value && env_var->exported)
		{
			key = ft_strcpy(env_var->key);
			if (!key)
				return (false);
			value = ft_strcpy(env_var->value);
			if (!value)
				return (false);
			if (!add_env_var(copy, key, value, true))
				return (false);
		}
		(*env_vars) = (*env_vars)->next;	
	}
	return (true);
}

t_list	*resolve_fork_ev(t_list *assignments, t_list *env_vars)
{
	t_list			*copy;

	copy = NULL;
	if (!resolve_assignments(assignments, &copy))
		return (NULL);
	if (!resolve_ev(&env_vars, &copy))
		return (NULL);
	return (copy);
}

bool	check_can_read(char *target)
{
	if (open(target, O_RDONLY) == -1)
	{
		printf("minishell: %s: %s\n", target, strerror(errno));
		return (false);
	}
	return (true);
}
