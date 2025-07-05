/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_backs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:27:32 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/05 10:10:41 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	delete_env_var(void *var)
{
	t_env_var *env_var;
	
	env_var = (t_env_var *)var;
	free(env_var->key);
	free(env_var->value);
	free(env_var);
}

void	delete_token(void *t)
{
	t_token *token;
	
	token = (t_token *)t;
	free(token->lexeme);
	free(token);
}
