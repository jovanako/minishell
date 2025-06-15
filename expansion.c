/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:26:35 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/15 20:01:11 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_env_var(void *var)
{
	t_env_var *env_var;
	
	env_var = (t_env_var *)var;
	free(env_var->key);
	free(env_var->value);
	free(env_var);
}

t_list	*parse_env_var(char *s)
{
	char		*equals;
	int			key_len;
	int			value_len;
	t_env_var	*new_var;
	
	new_var = malloc (sizeof(t_list));
	if (!new_var)
		return ((void *)0);
	equals = ft_strchr(s, '=');
	key_len = equals - s;
	new_var->key = ft_substr(s, 0, key_len);
	if (!(new_var->key))
		return ((void *)0);
	value_len = ft_strlen(s) - (key_len + 1);
	new_var->value = ft_substr(s, key_len + 1, value_len);
	if (!(new_var->value))
		return ((void *)0);
	return (ft_lstnew(new_var));
}

t_list	*copy_env_vars(char *envp[])
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
			ft_lstclear(&env_vars, &delete_token);
			return ((void *)0);
		}
		ft_lstadd_back(&env_vars, current_node);
	}
	return (env_vars);
}

// void	expand_variables(t_list *tokens)
// {
// 	t_token *token;

// 	ft_lstiter(tokens, &expand);
// }