/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empty_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:33:14 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/23 19:44:45 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static void	remove_in_rest(t_list *tokens, t_list *to_del)
{
	while (tokens)
	{
		if (tokens->next == to_del)
		{
			tokens->next = tokens->next->next;
			ft_lstdelone(to_del, delete_token);
		}
		tokens = tokens->next;
	}
}

static t_list	*remove_token(t_token_context *ctx, t_list *to_del)
{
	if (ctx->tokens == to_del)
	{
		ctx->tokens = ctx->tokens->next;
		ft_lstdelone(to_del, delete_token);
		return (ctx->tokens);
	}
	remove_in_rest(ctx->tokens, to_del);
	return (ctx->tokens->next);
}

void	remove_empty_tokens(t_token_context *ctx)
{
	t_list	*tokens;
	t_token	*token;

	tokens = ctx->tokens;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->type != NULL_TERMINATOR_TOKEN
			&& ft_strlen(token->lexeme) == 0)
			tokens = remove_token(ctx, tokens);
		else		
			tokens = tokens->next;
	}
}