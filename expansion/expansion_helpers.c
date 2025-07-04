/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:21:46 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/03 08:40:03 by jkovacev         ###   ########.fr       */
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

bool	is_valid_env_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	is_unquoted(char c)
{
	return (c != '\'' && c != '"' && c != '\0');
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

bool	handle_dollar(t_expansion_context *ctx, t_list *env_vars, int *i)
{
	char		*var_key;
	t_env_var	*var;
	
	if (!append_slice(ctx, &(ctx->lexeme[*i])))
		return (false);
	(*i)++;
	var_key = extract_var_key(ctx, i);
	if (!var_key)
		return (false);
	var = (t_env_var *)ft_lstfind(env_vars, &get_env_value, var_key);
	free(var_key);
	if (var)
		append_value(ctx, var->value);
	return (true);
}
