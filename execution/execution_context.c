/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_context.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:42:14 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/29 20:41:29 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_exec_ctx	*new_exec_ctx(t_parse_ctx *p_ctx, t_list *env_vars, int status)
{
	t_exec_ctx	*ctx;

	ctx = malloc(sizeof(t_exec_ctx));
	if (!ctx)
		return (NULL);
	ctx->commands = p_ctx->commands;
	ctx->env_vars = env_vars;
	ctx->exit = false;
	ctx->error = false;
	ctx->status = status;
	return (ctx);
}

void *free_exec_ctx(t_exec_ctx *ctx)
{
	free(ctx);
	return (NULL);
}