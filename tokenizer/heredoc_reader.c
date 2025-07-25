/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:00:49 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/25 19:28:03 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

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
	if (context->current - context->start == 0)
	{
		context->error = "syntax error near unexpected token 'newline'";
		return (true);
	}
	return (add_token(context, HEREDOC_TOKEN));
}
