/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:26:35 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/03 08:40:16 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static bool	free_result_and_return(t_expansion_context *ctx)
{
	free(ctx->result);
	return (false);
}

static bool	expand_word(t_token *token, t_list *env_vars)
{
	t_expansion_context ctx;

	ctx = (t_expansion_context){ .lexeme = token->lexeme, .result = "\0" };
	while (token->lexeme[ctx.current])
	{
		if (token->lexeme[ctx.current] == '\'' && !slice_single_quoted(&ctx))
			return (free_result_and_return(&ctx));
		if (token->lexeme[ctx.current] == '"' && !slice_double_quoted(&ctx, env_vars))
			return (free_result_and_return(&ctx));
		if (!slice_unquoted(&ctx, env_vars))
			return (free_result_and_return(&ctx));
	}
	free(token->lexeme);
	token->lexeme = ctx.result;
	return (true);
}

static bool	expand(void *content, void *env_vars)
{
	t_token *token;
	bool	success;

	(void)env_vars;
	success = true;
	token = (t_token *)content;
	if (token->type == WORD_TOKEN || token->type == ASSIGNMENT_TOKEN)
		success = expand_word(token, (t_list *)env_vars);
	return (success);
}

bool	expand_variables(t_list *tokens, t_list *env_vars)
{
	t_list	*current_token;

	current_token = tokens;
	while (current_token)
	{
		if (!expand(current_token->content, env_vars))
			return (false);
		current_token = current_token->next;
	}
	return (true);
}