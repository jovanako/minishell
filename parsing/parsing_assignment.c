/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_assignment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:19:27 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/26 19:24:48 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool 	parse_assignment(t_parse_ctx *ctx, t_command *command)
{
	t_token			*token;
	t_assignment	*assignment;
	t_list			*node;
	int				i;

	token = get_current(ctx);
	assignment = malloc(sizeof(t_assignment));
	if (!assignment)
		return (false);
	i = 0;
	while (token->lexeme[i] != '=')
		i++;
	assignment->key = ft_substr(token->lexeme, 0, i);
	if (!assignment->key)
		return (false);
	assignment->value = ft_substr(token->lexeme, i + 1,
		ft_strlen(token->lexeme) - i - 1);
	if (!assignment->value)
		return (false);
	node = ft_lstnew(assignment);
	if (!node)
		return(false);
	ft_lstadd_back(&(command->assignments), node);
	return (true);
}

bool	parse_assignment_list(t_parse_ctx *ctx, t_command *command)
{
	while (is_current_type(ctx, ASSIGNMENT_TOKEN))
	{
		if (!parse_assignment(ctx, command))
			return (false);
		p_advance(ctx);
	}
	return (true);
}
