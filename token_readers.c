/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_readers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:09:49 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/17 13:19:55 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_new_token(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == ' ' || c == '=');
}

static bool quotes_are_open(bool quotes_closed, bool double_quotes_closed)
{
	return (!quotes_closed || !double_quotes_closed);
}

static char start_matches(t_token_context *context, char c)
{
	return (context->line[context->start] == c);
}

bool	read_word(t_token_context *context)
{
	bool	quotes_closed;
	bool	double_quotes_closed;

	quotes_closed = !start_matches(context, '\'');
	double_quotes_closed = !start_matches(context, '"');
	while (peek(context) != '\0'
		&& (!is_new_token(peek(context)) 
			|| quotes_are_open(quotes_closed, double_quotes_closed)))
	{
		if (peek(context) == '"' && quotes_closed)
			double_quotes_closed = !double_quotes_closed;
		else if (peek(context) == '\'' && double_quotes_closed)
			quotes_closed = !quotes_closed;
		advance(context);
	}
	if (quotes_are_open(quotes_closed, double_quotes_closed))
		context->error = "invalid input";
	return (add_token(context, WORD_TOKEN));
}

bool	read_greater_than(t_token_context *context)
{
	if (match('>', context))
		return (add_token(context, APPEND_TOKEN));
	return (add_token(context, OUTPUT_REDIR_TOKEN));
}