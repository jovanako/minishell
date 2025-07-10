/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:02:51 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/10 20:55:28 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	print_token(void *t) // delete later
// {
// 	t_token *token;

// 	token = (t_token *)t;
// 	printf("type: %d lexeme: %s\n", token->type, token->lexeme);
// }

bool	add_token(t_token_context *context, t_token_type type)
{
	t_token	*token;
	t_list	*node;
	size_t	lexeme_len;

	lexeme_len = context->current - context->start;
	token = malloc(sizeof(t_token));
	if (!token)
		return (false);
	token->type = type;
	token->lexeme = ft_substr(context->line, context->start, lexeme_len);
	if (!token->lexeme)
		return (false);
	node = ft_lstnew(token);
	if (!node)
		return (false);
	ft_lstadd_back(&(context->tokens), node);
	return (true);
}

static bool	read_token(t_token_context *context)
{
	char	c;
	bool	success;
	
	c = advance(context);
	if (c == '<')
		success = read_less_than(context);
	else if (c == '>')
		success = read_greater_than(context);
	else if (c == '|')
		success = add_token(context, PIPE_TOKEN);
	else if (c == ' ' || c == '\t')
		return (true);
	else if (c == '\0')
		success = add_token(context, NULL_TERMINATOR_TOKEN);
	else
		success = read_word(context);
	return (success);
}

bool	tokenize(t_token_context *ctx)
{
	while (ctx->line[ctx->start])
	{
		ctx->start = ctx->current;
		if (!read_token(ctx))
		{
			ft_lstclear(&(ctx->tokens), &delete_token);
			return (false);
		}
		if (ctx->error)
		{
			ft_lstclear(&(ctx->tokens), &delete_token);
			printf("minishell: %s\n", ctx->error);
			return (false);
		}
	}
	return (true);
}
