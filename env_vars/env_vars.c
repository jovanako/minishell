/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:03:55 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/04 16:01:02 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_vars.h"

static t_list	*parse_env_var(char *s)
{
	char		*equals;
	int			key_len;
	int			value_len;
	t_env_var	*new_var;
	
	new_var = malloc (sizeof(t_env_var));
	if (!new_var)
		return (NULL);
	equals = ft_strchr(s, '=');
	key_len = equals - s;
	new_var->key = ft_substr(s, 0, key_len);
	if (!(new_var->key))
		return (NULL);
	value_len = ft_strlen(s) - (key_len + 1);
	new_var->value = ft_substr(s, key_len + 1, value_len);
	if (!(new_var->value))
		return (NULL);
	new_var->exported = true;
	return (ft_lstnew(new_var));
}

bool	is_valid_env_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

t_list	*create_env_vars(char *envp[])
{
	int		i;
	t_list	*env_vars;
	t_list	*current_node;

	i = 0;
	env_vars = NULL;	
	while (envp[i])
	{
		current_node = parse_env_var(envp[i++]);
		if (!current_node)
		{
			ft_lstclear(&env_vars, &delete_env_var);
			return (NULL);
		}
		ft_lstadd_back(&env_vars, current_node);
	}
	return (env_vars);
}
