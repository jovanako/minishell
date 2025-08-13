/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_context.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:02:50 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/31 20:47:14 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token_context	*new_ctx(char *input)
{
	t_token_context	*ctx;

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
	if (!ctx)
		return (NULL);
	ft_lstclear(&(ctx->tokens), &delete_token);
	free(ctx);
	return (NULL);
}
