/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:00:49 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/22 20:38:13 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../err_printf/err_printf.h"
#include "tokenizer.h"

static bool	is_valid_delimiter(char c)
{
	return (c != '<' && c != '>' && c != '|' && c != '&');
}

bool	read_heredoc_delimiter(t_token_context *context)
{
	context->start = context->current;
	while (context->line[context->start] == ' '
		|| context->line[context->start] == '\t')
		context->start++;
	context->current = context->start;
	while (context->line[context->current] != ' '
		&& context->line[context->current] != '\t'
		&& context->line[context->current] != '\0')
		advance(context);
	if (context->current - context->start == 0
		|| !is_valid_delimiter(context->line[context->start]))
	{
		err_printf("minishell: syntax error near unexpected token `newline'\n");
		context->error = true;
		return (true);
	}
	return (add_token(context, HEREDOC_TOKEN));
}
