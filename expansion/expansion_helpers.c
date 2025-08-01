/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:21:46 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/29 17:53:56 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*extract_var_key(t_expansion_context *ctx, int *start)
{
	char	*result;
	int		end;

	end = *start;
	if (ft_isdigit(ctx->lexeme[end]))
		end++;
	else
	{
		while (ft_isalnum(ctx->lexeme[end]) || ctx->lexeme[end] == '_')
			end++;	
	}
	result = ft_substr(ctx->lexeme, *start, end - *start);
	*start = end;
	ctx->current = end;
	return (result);
}

bool	append_value(t_expansion_context *ctx, char *var_value)
{
	char	*tmp;

	tmp = ctx->result;
	ctx->result = ft_strjoin(ctx->result, var_value);
	free(tmp);
	if (!(ctx->result))
		return (false);
	return (true);
}

bool	is_unquoted(char c)
{
	return (c != '\'' && c != '"' && c != '\0');
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

bool	handle_exit_expand(t_expansion_context *ctx, int *i)
{
	if (ctx->lexeme[*i] != '?')
		return (false);
	append_value(ctx, ft_itoa(ctx->exit_status));
	// append_value(ctx, "0");
	(*i)++;
	ctx->current = *i;
	return (true);
}
