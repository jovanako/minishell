/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_backs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:27:32 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/02 20:44:12 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (len != (int)ft_strlen(var->key))
		return (false);
	return (ft_strncmp(var->key, k, len) == 0);
}

void	delete_token(void *t)
{
	t_token *token;
	
	token = (t_token *)t;
	free(token->lexeme);
	free(token);
}
