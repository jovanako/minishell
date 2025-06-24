/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:53:41 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/24 22:04:20 by jkovacev         ###   ########.fr       */
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

bool	is_valid_identifier(t_token_context *ctx)
{
	int	i;

	i = ctx->start;
	if (!ft_isalpha(ctx->line[i]) && ctx->line[i] != '_')
		return (false);
	while (ctx->line[i] && ctx->line[i] != '=')
	{
		if (!ft_isalnum(ctx->line[i]) && ctx->line[i] != '_')
			return (false);
		i++;
	}
	return (ctx->line[i] == '=');
}
