/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: culbrich <culbrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:55:34 by culbrich          #+#    #+#             */
/*   Updated: 2025/06/27 14:41:54 by culbrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

// prints all environment variables
int	ft_env(t_list *lst)
{
	t_env_var	*env_var;

	while (lst)
	{
		env_var = (t_env_var *)lst->content;
		if (env_var->value)
			printf("%s=%s\n", env_var->key, env_var->value);
		lst = lst->next;
	}
	return (0);
}

// modifies a given environment variable to a new value
int	ft_modenv(t_list *lst, char *key)
{
	t_env_var	*env_var;

	if (!lst)
		return (1);
	env_var = (t_env_var *)lst->content;
	env_var->value = key;
	lst->content = (void *)env_var;
	return (0);
}

// returns a pointer to the element of an env var with given key
t_list	*ft_getenv(t_list *lst, char *key)
{
	t_env_var	*env_var;

	if (!key)
		return (NULL);
	while (lst)
	{
		env_var = (t_env_var *)lst->content;
		if (ft_strncmp(env_var->key, key, ft_strlen(key)))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

char	*ft_getenv_v(t_list *lst)
{
	t_env_var	*env_var;

	if (lst)
	{
		env_var = (t_env_var *)lst->content;
		if (env_var->value)
			return (env_var->value);
	}
	return (NULL);
}

char	*ft_getenv_k(t_list *lst)
{
	t_env_var	*env_var;

	if (lst)
	{
		env_var = (t_env_var *)lst->content;
		if (env_var->key)
			return (env_var->key);
	}
	return (NULL);
}
