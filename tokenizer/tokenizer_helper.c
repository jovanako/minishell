/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:53:41 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/24 09:36:46 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	peek(t_token_context *context)
{
	return (context->line[context->current]);
}

char	advance(t_token_context *context)
{
	return (context->line[(context->current)++]);
}

bool	match(char expected_char, t_token_context *context)
{
	char	current_char;

	current_char = context->line[(context->current)];
	if (current_char == '\0')
		return (false);
	if (current_char != expected_char)
		return (false);
	context->current++;
	return (true);
}
