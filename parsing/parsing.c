/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:10:24 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/28 21:06:26 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	parse_simple_command(t_parse_ctx *ctx)
{
	t_command	*command;
	t_list		*node;

	command = malloc(sizeof(t_command));
	if (!command)
		return (false);
	command->assignments = NULL;
	command->redirections = NULL;
	if (!parse_assignment_list(ctx, command))
		return (false);
	if (!parse_redirection_list(ctx, command))
		return (false);
	if (!parse_argv(ctx, command))
		return (false);
	if (!parse_redirection_list(ctx, command))
		return (false);	
	node = ft_lstnew(command);
	if (!node)
		return (false);
	ft_lstadd_back(&ctx->commands, node);
	return (true);
}

bool	parse_command_line(t_parse_ctx *ctx)
{
	if (!parse_simple_command(ctx))
		return (false);
	
	while (p_match(ctx, PIPE_TOKEN))
	{
		if (!parse_simple_command(ctx))
			return (false);
	}	
	return (true);
}

t_parse_ctx	*parse(t_token_context *t_ctx)
{
	t_parse_ctx *ctx;
	t_token		*token;
	
	if (!t_ctx)
		return (NULL);
	token = t_ctx->tokens->content;
	if (ft_strcmp(token->lexeme, "|") == 0)
		printf("minishell: syntax error near unexpected token `%c'\n", '|');
	ctx = new_parsing_ctx(t_ctx);
	if (!ctx)
		return (NULL);
	if (!(parse_command_line(ctx)))
	{
		free_parsing_ctx(ctx);
		return (NULL);
	}
	return (ctx);
}