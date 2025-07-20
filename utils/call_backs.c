/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_backs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:27:32 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/19 10:33:36 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	delete_token(void *t)
{
	t_token *token;
	
	token = (t_token *)t;
	free(token->lexeme);
	free(token);
}

bool	match_assignment_key(void *a, void *k)
{
	t_assignment	*assignment;
	char			*key;
	
	key = k;
	assignment = a;
	return (ft_strcmp(assignment->key, key) == 0);
}