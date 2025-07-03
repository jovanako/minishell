/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slicing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:33:19 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/03 08:40:28 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	append_slice(t_expansion_context *ctx, char *end)
{
	char	*slice;
	char	*tmp;
	int		len;

	len = end - &(ctx->lexeme[ctx->current]);
	slice = ft_substr(ctx->lexeme, ctx->current, len);
	if (!slice)
		return (false);
	ctx->current = ctx->current + len + 1;
	tmp = ctx->result;
	ctx->result = ft_strjoin(ctx->result, slice);
	if (*tmp)
		free(tmp);
	free(slice);
	if (!(ctx->result))
		return (false);
	return (true);
}

bool	slice_single_quoted(t_expansion_context *ctx)
{
	char	*end;

	ctx->current++;
	end = ft_strchr(&(ctx->lexeme[ctx->current]), '\'');
	return (append_slice(ctx, end));
}

bool	slice_double_quoted(t_expansion_context *ctx, t_list *env_vars)
{
	int			i;

	ctx->current++;
	i = ctx->current;
	while (ctx->lexeme[i] != '"')
	{
		if (ctx->lexeme[i] == '$' && is_valid_env_var_char(ctx->lexeme[i + 1]))
		{
			if (!handle_dollar(ctx, env_vars, &i))
				return (false);
		}
		else
			i++;
	}
	if (!append_slice(ctx, &(ctx->lexeme[i])))
		return (false);
	ctx->current = i + 1;
	return (true);
}

bool	slice_unquoted(t_expansion_context *ctx, t_list *env_vars)
{
	int	i;

	i = ctx->current;
	while (is_unquoted(ctx->lexeme[i]))
	{
		if (ctx->lexeme[i] == '$' && is_valid_env_var_char(ctx->lexeme[i + 1]))
		{
			if (!handle_dollar(ctx, env_vars, &i))
				return (false);
		}
		else if (ctx->lexeme[i] == '$' && is_quote(ctx->lexeme[i + 1]))
		{
			if (!append_slice(ctx, &(ctx->lexeme[i])))
				return (false);
			i++;
		}
		else
			i++;
	}
	if (!append_slice(ctx, &(ctx->lexeme[i])))
		return (false);
	ctx->current = i;
	return (true);
}
