/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:22:25 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/27 12:42:49 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_redirect_type	resolve_redirect_type(t_token_type token_type)
{
	if (token_type == INPUT_REDIR_TOKEN)
		return (INPUT_REDIRECT);
	if (token_type == OUTPUT_REDIR_TOKEN)
		return (OUTPUT_REDIRECT);
	if (token_type == APPEND_TOKEN)
		return (APPEND_REDIRECT);
	if (token_type == HEREDOC_TOKEN)
		return (HEREDOC_REDIRECT);
	return (UNKNOWN_REDIRECT);
}

static bool add_redirection(t_command *cmd, t_redirection *redir)
{
	t_list			*node;
	
	node = ft_lstnew(redir);
	if (!node)
		return (false);
	ft_lstadd_back(&(cmd->redirections), node);
	return (true);
}

static bool	parse_redirection(t_parse_ctx *ctx, t_command *command)
{
	t_token			*token;
	t_redirection	*redirection;
	
	token = (t_token *)ctx->current->content;
	redirection = malloc(sizeof(t_redirection));
	if (!redirection)
		return (false);
	redirection->type = resolve_redirect_type(token->type);
	if (redirection->type == UNKNOWN_REDIRECT)
		return (false);
	if (redirection->type != HEREDOC_REDIRECT)
	{
		p_advance(ctx);
		token = (t_token *)ctx->current->content;
		if (!is_current_type(ctx, WORD_TOKEN))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			ctx->error = true;
			return (true);
		}	 
	}
	redirection->target = token->lexeme;
	return (add_redirection(command, redirection));
}

bool 	parse_redirection_list(t_parse_ctx *ctx, t_command *command)
{
	while (is_current_type(ctx, INPUT_REDIR_TOKEN)
		|| is_current_type(ctx, OUTPUT_REDIR_TOKEN)
		|| is_current_type(ctx, APPEND_TOKEN)
		|| is_current_type(ctx, HEREDOC_TOKEN))
	{
		if (!parse_redirection(ctx, command))
			return (false);	
		if (ctx->error)
			return (true);
		p_advance(ctx);
	}
	return (true);
}