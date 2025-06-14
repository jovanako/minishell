/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:53:41 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/14 09:54:27 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_token(void *t)
{
	t_token *token;
	
	token = (t_token *)t;
	free(token->lexeme);
	free(token);
}

char	peek(t_token_context *context)
{
	return (context->line[context->current]);
}

char	advance(t_token_context *context)
{
	return (context->line[(context->current)++]);
}

bool	match(char expected_char, t_token_context *context)
{
	char	current_char;

	current_char = context->line[(context->current)];
	if (current_char == '\0')
		return (false);
	if (current_char != expected_char)
		return (false);
	context->current++;
	return (true);
}

bool	read_expansion(t_token_context *context)
{
	while (ft_isalnum(peek(context)) || peek(context) == '_')
		advance(context);
	return (add_token(context, EXPANSION_TOKEN));
}