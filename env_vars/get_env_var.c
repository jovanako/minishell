/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 10:05:14 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/05 10:09:53 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_vars.h"

static bool	get_env_value(void *content, void *var_key)
{
	t_env_var	*var;
	char		*k;
	size_t		len;

	var = content;
	k = var_key;
	len = ft_strlen(k);
	if (len != ft_strlen(var->key))
		return (false);
	return (ft_strncmp(var->key, k, len) == 0);
}

t_env_var	*get_env_var(t_list *env_vars, char *key)
{
	return (ft_lstfind(env_vars, &get_env_value, key));
}
