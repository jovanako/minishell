/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_readers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:09:49 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/14 10:59:33 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	read_expansion(t_token_context *context)
{
	while (ft_isalnum(peek(context)) || peek(context) == '_')
		advance(context);
	return (add_token(context, EXPANSION_TOKEN));
}

bool	read_dollar(t_token_context *context)
{
	if (match('?', context))
		return (add_token(context, EXIT_STATUS_TOKEN));
	if (ft_isdigit(peek(context)))
	{
		advance(context);
		return (add_token(context, EXPANSION_TOKEN));
	}
	return read_expansion(context);
}

bool	read_literal(t_token_context *context)
{
	while (peek(context) != '\'' && peek(context) != '\0')
		advance(context);
	if (peek(context) == '\0')
	{
		context->error = "Unterminated string";
		return (true);
	}
	context->start++;
	if (add_token(context, LITERAL_TOKEN))
	{
		advance(context);
		return (true);
	}
	return (false);
}