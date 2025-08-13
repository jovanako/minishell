/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: culbrich <culbrich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:12:21 by culbrich          #+#    #+#             */
/*   Updated: 2025/08/07 13:12:21 by culbrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../built-ins/built_ins.h"

char	*heredoc_expand_dollar(int *start, char *input, t_exec_ctx *ctx)
{
	(*start)++;
	if (input[*start] && input[*start] == '?')
	{
		(*start)++;
		return (ft_itoa(ft_get_last_sig_exit(ctx->status)));
	}
	else
		return (ft_strdup("$"));
}

int	heredoc_event_hook(void)
{
	if (g_last_sig == SIGINT)
		rl_done = 1;
	return (0);
}

static int	hd_append_slice(t_redirection *re, char **dl, int start, int end)
{
	char	*slice;

	slice = ft_substr(re->target, start, end - start);
	if (!slice)
		return (0);
	*dl = ft_strappend(*dl, slice);
	free(slice);
	if (!(*dl))
		return (0);
	return (1);
}

static int	hd_find_next_q(t_redirection *re, char **dl, char q, int *start)
{
	int	i;

	i = *start;
	while (re->target[i] != q)
	{
		if (!re->target[i++])
			return (0); // invalid input (2)
	}
	if (!(hd_append_slice(re, dl, *start, i)))
		return (0);
	*start = i + 1;
	return (1);
}

int	hd_quoted_dl_loop(t_redirection *redir, char **dl, int *start, char *q)
{
	int	i;

	i = *start;
	if (redir->target[i] == '\'' || redir->target[i] == '\"')
	{
		*q = redir->target[i++];
		if (!(hd_find_next_q(redir, dl, *q, &i)))
			return (0);
	}
	else
	{
		if (!(hd_append_slice(redir, dl, i, i + 1)))
			return (0);
		i++;
	}
	*start = i;
	return (1);
}
