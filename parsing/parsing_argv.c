/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 21:55:41 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/28 15:55:35 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_token_type	get_token_type(t_list *node)
{
	t_token	*token;
	
	if (!node)
		return (UNDEFINED);
	token = (t_token*)node->content;
	return token->type;
}

static int	size_of_argv(t_parsing_context *ctx)
{
	int		size;
	t_list	*node;
	
	size = 0;
	node = ctx->current;
	while (get_token_type(node) == WORD_TOKEN)
	{
		size++;
		node = node->next;	
	}
	return (size);
}

bool	parse_argv(t_parsing_context *ctx, t_command *command)
{
	int		i;
	char 	**argv;

	i = 0;
	argv = malloc(sizeof(char *) * (size_of_argv(ctx) + 1));
	while (get_token_type(ctx->current) == WORD_TOKEN)
	{
		argv[i++] = get_current(ctx)->lexeme;
		p_advance(ctx);
	}
	argv[i] = NULL;
	command->argv = argv;
	return (true);
}