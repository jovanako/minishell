/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_readers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:09:49 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/15 12:57:41 by jkovacev         ###   ########.fr       */
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
	return (add_token(context, WORD_TOKEN));
}