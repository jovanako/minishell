/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_context.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:16:18 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/26 19:24:48 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_parse_ctx	*new_parsing_ctx(t_token_context *t_ctx)
{
	t_parse_ctx	*ctx;

	ctx = malloc(sizeof(t_parse_ctx));
	if (!ctx)
		return (NULL);
	ctx->tokens = t_ctx->tokens;
	ctx->current = t_ctx->tokens;
	ctx->commands = NULL;
	ctx->error = false;
	return (ctx);
}

void	*free_parsing_ctx(t_parse_ctx *ctx)
{
	ft_lstclear(&(ctx->commands), &delete_command);
	free(ctx);
	return (NULL);
}