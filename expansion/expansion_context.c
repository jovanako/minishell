/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_context.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:05:37 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/19 17:21:12 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

t_expansion_context	*new_e_ctx(char *lexeme, int status)
{
	t_expansion_context	*ctx;

	ctx = malloc(sizeof(t_expansion_context));
	if (!ctx)
		return (NULL);
	ctx->current = 0;
	ctx->lexeme = lexeme;
	ctx->result = malloc(sizeof(char));
	if (!ctx->result)
	{
		free(ctx);
		return (NULL);
	}
	ctx->exit_status = status;
	return (ctx);
}

bool	*free_expansion_ctx(t_expansion_context *ctx)
{
	if (!ctx)
		return (false);
	free(ctx->result);
	free(ctx);
	return (false);
}