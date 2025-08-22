/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:10:24 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/22 19:31:18 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	parse_args_and_redirs(t_parse_ctx *ctx, t_command *command)
{
	while (!is_current_type(ctx, PIPE_TOKEN)
		&& !is_current_type(ctx, NULL_TERMINATOR_TOKEN))
	{
		if (is_current_type(ctx, WORD_TOKEN)
			&& !parse_argv(ctx, command))
			return (false);
		if ((is_current_type(ctx, INPUT_REDIR_TOKEN)
			|| is_current_type(ctx, OUTPUT_REDIR_TOKEN)
			|| is_current_type(ctx, APPEND_TOKEN)
			|| is_current_type(ctx, HEREDOC_TOKEN))
			&& !parse_redirection_list(ctx, command))
			return (false);		
	}
	return (true);
}

static bool	parse_simple_command(t_parse_ctx *ctx)
{
	t_command	*command;
	t_list		*node;

	command = malloc(sizeof(t_command));
	if (!command)
		return (false);
	command->assignments = NULL;
	command->redirections = NULL;
	command->argv = NULL;
	command->pid = -1;
	if (!parse_assignment_list(ctx, command))
		return (false);
	if (!parse_redirection_list(ctx, command))
		return (false);
	if (!parse_args_and_redirs(ctx, command))
		return (false);
	node = ft_lstnew(command);
	if (!node)
		return (false);
	ft_lstadd_back(&ctx->commands, node);
	return (true);
}

static bool	parse_command_line(t_parse_ctx *ctx)
{
	t_token	*current;

	if (!parse_simple_command(ctx))
		return (false);
	while (p_match(ctx, PIPE_TOKEN))
	{
		current = ctx->current->content;
		if (ft_strlen(current->lexeme) == 0)
		{
			printf("minishell: syntax error near unexpected token `%c'\n", '|');
			ctx->error = true;
			return (true);
		}
		if (!parse_simple_command(ctx))
			return (false);
	}
	return (true);
}

t_parse_ctx	*parse(t_token_context *t_ctx)
{
	t_parse_ctx	*ctx;
	t_token		*token;

	if (!t_ctx)
		return (NULL);
	token = t_ctx->tokens->content;
	ctx = new_parsing_ctx(t_ctx);
	if (ft_strcmp(token->lexeme, "|") == 0)
	{
		printf("minishell: syntax error near unexpected token `%c'\n", '|');
		ctx->error = true;
		return (ctx);
	}
	if (!ctx)
		return (NULL);
	if (!(parse_command_line(ctx)))
	{
		free_parsing_ctx(ctx);
		return (NULL);
	}
	return (ctx);
}
