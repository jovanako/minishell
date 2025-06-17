/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:11:24 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/17 12:57:30 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	read_less_than(t_token_context *context)
{
	if (match('<', context))
		return (read_heredoc_delimiter(context));
	return (add_token(context, INPUT_REDIR_TOKEN));
}

bool	read_heredoc_delimiter(t_token_context *context)
{
	context->start = context->current;
	while (context->line[context->start] == ' '
		|| context->line[context->start] == '\t')
		context->start++;
	context->current = context->start;
	while (context->line[context->current] != '\0')
		advance(context);
	if (context->current - context->start == 0)
	{
		context->error = "syntax error near unexpected token 'newline'";
		return (true);
	}
	return (add_token(context, HEREDOC_TOKEN));
}
