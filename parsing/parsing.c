/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:10:24 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/22 12:32:34 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	parse_simple_command(t_parsing_context *ctx)
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

bool	parse_command_line(t_parsing_context *ctx)
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

bool	parse(t_parsing_context *ctx)
{
	if (!(parse_command_line(ctx)))
	{
		ft_lstiter(ctx->commands, &delete_command);
		return (false);
	}
	return (true);
}