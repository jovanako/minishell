/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:02:51 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/15 13:23:24 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	read_token(t_token_context *context)
{
	char	c;
	bool	success;
	
	success = false;
	c = advance(context);
	if (c == '<')
		success = read_less_than(context);
	else if (c == '>')
		success = read_greater_than(context);
	else if (c == '|')
		success = add_token(context, PIPE_TOKEN);
	else if (c == '=')
		success = add_token(context, EQUALS_TOKEN);
	else if (c == ' ' || c == '\t' || c == '\0')
		return ;
	else if (c == '\0')
		success = add_token(context, NULL_TERMINATOR_TOKEN);
	else
		success = read_word(context);
	if (!success)
		ft_lstclear(&(context->tokens), &delete_token);
}

t_list	*tokenize(char *s)
{
	t_token_context	context;

	context = (t_token_context){ .line = s };
	while (s[context.start])
	{
		context.start = context.current;
		read_token(&context);
	}
	return (context.tokens);
}
