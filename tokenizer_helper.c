/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:53:41 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/14 22:15:21 by jkovacev         ###   ########.fr       */
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

char start_matches(t_token_context *context, char c)
{
	return (context->line[context->start] == c);
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
