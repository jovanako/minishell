/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:26:49 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/26 19:24:48 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

bool	is_current_type(t_parse_ctx *ctx, t_token_type token_type)
{
	t_token	*token;

	token = get_current(ctx);
	return (token && token->type == token_type);
}

bool	is_at_end(t_parse_ctx *ctx)
{
	return (is_current_type(ctx, NULL_TERMINATOR_TOKEN));
}

bool	p_match(t_parse_ctx *ctx, t_token_type token_type)
{
	if (is_at_end(ctx))
		return (false);
	if (is_current_type(ctx, token_type))
	{
		p_advance(ctx);
		return (true);
	}
	return (false);
}

t_token	*get_current(t_parse_ctx *ctx)
{
	if (ctx->current)
		return ((t_token *)ctx->current->content);
	return (NULL);
}

t_token	*p_advance(t_parse_ctx *ctx)
{
	t_list	*temp;

	temp = ctx->current;
	if (!is_at_end(ctx))
		ctx->current = ctx->current->next;
	return ((t_token *)temp->content);
}
