/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:10:24 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/25 21:30:32 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

bool	parse_simple_command(t_parsing_context *ctx)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (false);
	if (!parse_assignment_list(ctx, command))
		return (false);
	// ft_lstiter(command->assignments, &print_assignment);
	if (!parse_redirection_list(ctx, command))
		return (false);
	// parse command
	if (!parse_redirection_list(ctx, command))
		return (false);
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
	// TODO: clean up parsing context if failure
	return (parse_command_line(ctx));
}