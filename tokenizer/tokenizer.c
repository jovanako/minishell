/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:02:51 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/26 20:07:07 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	print_token(void *t) // delete later
// {
// 	t_token *token;

// 	token = (t_token *)t;
// 	printf("type: %d lexeme: %s\n", token->type, token->lexeme);
// }

static bool	read_less_than(t_token_context *context)
{
	if (match('<', context))
		return (read_heredoc_delimiter(context));
	return (add_token(context, INPUT_REDIR_TOKEN));
}

static bool	read_greater_than(t_token_context *context)
{
	if (match('>', context))
		return (add_token(context, APPEND_TOKEN));
	return (add_token(context, OUTPUT_REDIR_TOKEN));
}

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

t_token_context	*tokenize(char *input)
{
	t_token_context	*ctx;

	if (!input)
		return (NULL);
	ctx = new_ctx(input);
	if (!ctx)
		return (NULL);
	while (ctx->line[ctx->start])
	{
		ctx->start = ctx->current;
		if (!read_token(ctx))
			return (free_token_ctx(ctx));
		if (ctx->error)
			return (ctx);
	}
	return (ctx);
}
