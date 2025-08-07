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

char    *heredoc_expand_dollar(int *start, char *input, t_exec_ctx *ctx)
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
