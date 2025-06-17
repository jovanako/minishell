/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:21:46 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/17 16:00:51 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	slice_single_quoted(t_expansion_context *ctx)
{
	char	*end;
	char	*slice;
	char	*tmp;
	int		len;

	ctx->current++;
	end = ft_strchr(&(ctx->lexeme[ctx->current]), '\'');
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
