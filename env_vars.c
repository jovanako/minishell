/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:03:55 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/20 19:31:20 by jkovacev         ###   ########.fr       */
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

bool	get_env_value(void *content, void *var_key)
{
	t_env_var	*var;
	char		*k;
	int			len;
	
	var = (t_env_var *)content;
	k = (char *)var_key;
	len = ft_strlen(var_key);
	return (ft_strncmp(var->key, k, len) == 0);
}

bool	append_value(t_expansion_context *ctx, char *var_value)
{
	char	*tmp;

	tmp = ctx->result;
	ctx->result = ft_strjoin(ctx->result, var_value);
	if (*tmp)
		free(tmp);
	if (!(ctx->result))
		return (false);
	return (true);
}

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
			ft_lstclear(&env_vars, &delete_env_var);
			return (NULL);
		}
		ft_lstadd_back(&env_vars, current_node);
	}
	return (env_vars);
}
