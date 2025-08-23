/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:21:46 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/23 18:00:49 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../built-ins/built_ins.h"

char	*extract_var_key(t_expand_ctx *ctx, int *start)
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

bool	append_value(t_expand_ctx *ctx, char *var_value)
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

bool	handle_exit_expand(t_expand_ctx *ctx, int *i)
{
	int		status;
	char	*status_str;

	status = ft_get_last_sig_exit(ctx->exit_status);
	status_str = ft_itoa(status);
	if (!status_str)
		return (false);
	if (!append_value(ctx, status_str))
		return (false);
	free(status_str);
	(*i)++;
	ctx->current = *i;
	return (true);
}
