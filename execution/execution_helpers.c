/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:32:00 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/08 21:49:16 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**ev_list_to_arr(t_list *env_vars)
{
	int			len;
	int			i;
	char		**result;
	t_env_var	*var;
	char		*str_var;

	i = 0;
	len = ft_lstsize(env_vars);
	result = malloc((len + 1) * sizeof(char *));
	if (!result)
		return NULL;
	while (env_vars)
	{
		var = (t_env_var *)env_vars->content;
		str_var = ft_strjoin(var->key, "=");
		// TODO check ft_strjoin success and free result and elements on fail
		str_var = ft_strjoin(str_var, var->value);
		// TODO check ft_strjoin success and free result and elements on fail
		result[i++] = str_var;
		env_vars = env_vars->next;
	}
	result[i] = NULL;
	return (result);
}

t_list	*resolve_fork_ev(t_list *assignments, t_list *env_vars)
{
	t_list			*copy;
	t_assignment	*assignment;
	t_env_var		*env_var;

	copy = NULL;
	while (assignments)
	{
		assignment = assignments->content;
		// TODO make a copy of key and value strings
		if (!add_env_var(&copy, assignment->key, assignment->value, true))
			return (NULL);
		assignments = assignments->next;
	}
	while (env_vars)
	{
		env_var = env_vars->content;
		if (env_var->exported)
		{
			// TODO make a copy of key and value strings
			if (!add_env_var(&copy, env_var->key, env_var->value, true))
				return (NULL);
		}
		env_vars = env_vars->next;	
	}
	return (copy);
}
