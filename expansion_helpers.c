/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:21:46 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/20 19:51:46 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	append_slice(t_expansion_context *ctx, char *end)
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

bool	slice_double_quoted(t_expansion_context *ctx, t_list *env_vars)
{
	int			i;
	char		*var_key;
	t_env_var	*var;

	ctx->current++;
	i = ctx->current;
	while (ctx->lexeme[i] != '"')
	{
		if (ctx->lexeme[i] == '$')
		{
			if (!append_slice(ctx, &(ctx->lexeme[i])))
				return (false);
			i++;
			var_key = extract_var_key(ctx, &i);
			if (!var_key)
				return (false);
			var = (t_env_var *)ft_lstfind(env_vars, &get_env_value, var_key);
			if (var)
				append_value(ctx, var->value);
		}
		else
			i++;
	}
	if (!append_slice(ctx, &(ctx->lexeme[i])))
		return (false);
	ctx->current = i + 1;
	return (true);
}
