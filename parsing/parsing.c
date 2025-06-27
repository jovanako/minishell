/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:10:24 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/27 07:31:09 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../minishell.h"

static void	print_assignment(void *var) // delete later
{
	t_assignment *assignment;

	assignment = (t_assignment *)var;
	printf("key: %s value: %s\n", assignment->key, assignment->value);
}

static void print_redirection(void *var) // delete later
{
	t_redirection *redirection;
	
	redirection = (t_redirection *)var;
	printf("type: %d target: %s\n", redirection->type, redirection->target);
}

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
	
	printf("assignments ->\n"); // delete this
	ft_lstiter(command->assignments, &print_assignment); // delete this
	
	if (!parse_redirection_list(ctx, command))
		return (false);
	// parse command
	if (!parse_redirection_list(ctx, command))
		return (false);

	printf("redirections ->\n"); // delete this
	ft_lstiter(command->redirections, &print_redirection); // delete this
		
	node = ft_lstnew(command);
	if (!node)
		return (false);
	ft_lstadd_back(&ctx->syntax_tree, node);
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