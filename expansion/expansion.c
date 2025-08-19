/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:26:35 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/19 16:29:42 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static bool	expand_word(t_token *token, t_list *env_vars, int status)
{
	t_expansion_context	*ctx;

	ctx = new_e_ctx(token->lexeme, status);
	ctx->result = malloc(sizeof(char));
	if (!ctx->result)
		return (false);
	ft_bzero(ctx->result, 1);
	while (token->lexeme[ctx->current])
	{
		if (token->lexeme[ctx->current] == '\'' && !slice_single_quoted(ctx))
			return (free_expansion_ctx(ctx));
		if (token->lexeme[ctx->current] == '"'
			&& !slice_double_quoted(ctx, env_vars))
			return (free_expansion_ctx(ctx));
		if (!slice_unquoted(ctx, env_vars))
			return (free_expansion_ctx(ctx));
	}
	free(token->lexeme);
	token->lexeme = ctx->result;
	free_expansion_ctx(ctx);
	return (true);
}

static bool	expand_token(void *content, void *env_vars, int status)
{
	t_token	*token;
	bool	success;

	success = true;
	token = (t_token *)content;
	if (token->type == WORD_TOKEN || token->type == ASSIGNMENT_TOKEN)
		success = expand_word(token, (t_list *)env_vars, status);
	return (success);
}

bool	expand_variables(t_list *tokens, t_list *env_vars, int status)
{
	t_list	*current_token;

	current_token = tokens;
	while (current_token)
	{
		if (!expand_token(current_token->content, env_vars, status))
			return (false);
		current_token = current_token->next;
	}
	return (true);
}

bool	handle_dollar(t_expansion_context *ctx, t_list *env_vars, int *i)
{
	char		*var_key;
	t_env_var	*var;

	if (!append_slice(ctx, &(ctx->lexeme[*i])))
		return (false);
	(*i)++;
	if (handle_exit_expand(ctx, i))
		return (true);
	var_key = extract_var_key(ctx, i);
	if (!var_key)
		return (false);
	var = get_env_var(env_vars, var_key);
	free(var_key);
	if (var)
		append_value(ctx, var->value);
	return (true);
}

bool	expand(t_token_context *ctx, t_list *env_vars, int status)
{
	if (!ctx)
		return (false);
	if (!expand_variables(ctx->tokens, env_vars, status))
	{
		ft_lstclear(&(ctx->tokens), &delete_token);
		return (false);
	}
	return (true);
}
