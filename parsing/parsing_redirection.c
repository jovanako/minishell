/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:22:25 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/27 06:43:03 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_redirect_type	resolve_redirect_type(t_token_type token_type)
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

bool	parse_redirection(t_parsing_context *ctx, t_command *command)
{
	t_token			*token;
	t_redirection	*redirection;
	t_list			*node;
	
	token = (t_token *)ctx->current->content;
	redirection = malloc(sizeof(t_redirection));
	if (!redirection)
		return (false);
	redirection->type = resolve_redirect_type(token->type);
	if (redirection->type == UNKNOWN_REDIRECT)
		return (false);
	p_advance(ctx);
	token = (t_token *)ctx->current->content;
	if (!is_current_type(ctx, WORD_TOKEN))
	{
		ctx->error = "Syntax error\n";
		return (false);
	}	 
	redirection->target = token->lexeme; 
	node = ft_lstnew(redirection);
	if (!node)
		return (false);
	ft_lstadd_back(&(command->redirections), node);
	return (true);
}

bool 	parse_redirection_list(t_parsing_context *ctx, t_command *command)
{
	while (is_current_type(ctx, INPUT_REDIR_TOKEN)
		|| is_current_type(ctx, OUTPUT_REDIR_TOKEN)
		|| is_current_type(ctx, APPEND_TOKEN)
		|| is_current_type(ctx, HEREDOC_TOKEN))
	{
		if (!parse_redirection(ctx, command))
			return (false);	
		p_advance(ctx);
	}
	return (true);
}