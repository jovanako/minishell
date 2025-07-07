/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: culbrich <culbrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:55:34 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/03 15:23:13 by culbrich         ###   ########.fr       */
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
		{
			ft_putstr_fd(env_var->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(env_var->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
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
		if (!ft_strcmp(env_var->key, key))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

// returns the value (str) of env pointed to by lst
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

// returns the key (str) of env pointed to by lst
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
