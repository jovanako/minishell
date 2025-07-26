/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_context.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:02:50 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/26 18:23:02 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token_context *new_ctx(char *input)
{
	t_token_context	*ctx;

	if (!input)
		return (NULL);
	ctx = malloc(sizeof(t_token_context));
	if (!ctx)
		return (NULL);
	ctx->line = input;
	ctx->start = 0;
	ctx->current = 0;
	ctx->tokens = NULL;
	ctx->error = false;
	return (ctx);
}

void	*free_token_ctx(t_token_context *ctx)
{
	ft_lstclear(&(ctx->tokens), &delete_token);
	free(ctx);
	return (NULL);
}