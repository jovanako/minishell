/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:32:00 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/22 18:23:01 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	**free_and_return(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i])
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
	return (NULL); 
}

char	**ev_list_to_arr(t_list *env_vars)
{
	int			i;
	char		**result;
	t_env_var	*var;
	char		*str_var1;
	char		*str_var2;

	i = 0;
	result = malloc((ft_lstsize(env_vars) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (env_vars)
	{
		var = (t_env_var *)env_vars->content;
		str_var1 = ft_strjoin(var->key, "=");
		if (!str_var1)
			return (free_and_return(result));
		str_var2 = ft_strjoin(str_var1, var->value);
		free(str_var1);
		if (!str_var2)
			return (free_and_return(result));
		result[i++] = str_var2;
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
	char			*key;
	char			*value;

	copy = NULL;
	while (assignments)
	{
		assignment = assignments->content;
		key = ft_strcpy(assignment->key);
		if (!key)
			return (NULL);
		value = ft_strcpy(assignment->value);
		if (!value)
			return (NULL);
		if (!add_env_var(&copy, key, value, true))
			return (NULL);
		assignments = assignments->next;
	}
	while (env_vars)
	{
		env_var = env_vars->content;
		if (env_var->value && env_var->exported)
		{
			key = ft_strcpy(env_var->key);
			if (!key)
				return (NULL);
			value = ft_strcpy(env_var->value);
			if (!value)
				return (NULL);
			if (!add_env_var(&copy, key, value, true))
				return (NULL);
		}
		env_vars = env_vars->next;	
	}
	return (copy);
}
