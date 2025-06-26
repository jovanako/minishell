/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_assignment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:19:27 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/25 20:42:06 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool 	parse_assignment(t_parsing_context *ctx, t_command *command)
{
	t_token			*token;
	t_assignment	*assignment;
	t_list			*node;
	int				i;

	token = (t_token *)ctx->current->content;
	assignment = malloc(sizeof(t_assignment));
	if (!assignment)
		return (false);
	i = 0;
	while (token->lexeme[i] != '=')
		i++;
	assignment->key = ft_substr(token->lexeme, 0, i);
	if (!assignment->key)
		return (false);
	assignment->value = ft_substr(token->lexeme, i + 1,	ft_strlen(token->lexeme) - i - 1);
	if (!assignment->value)
		return (false);
	node = ft_lstnew(assignment);
	if (!node)
		return(false);
	ft_lstadd_back(&(command->assignments), node);
	return (true);
}

bool	parse_assignment_list(t_parsing_context *ctx, t_command *command)
{
	while (p_match(ctx, ASSIGNMENT_TOKEN))
	{
		if (!parse_assignment(ctx, command))
			return (false);
	}
	return (true);
}