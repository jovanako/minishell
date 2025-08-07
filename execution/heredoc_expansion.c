/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:43:09 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/29 20:57:16 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

int close_heredoc(char *delimiter, int error)
{
    if (delimiter)
        free(delimiter);
    return (error);
}

static char *heredoc_append_word(int *start, char *input)
{
    char    *tmp;
    int     i;

    i = *start;
    while (input[i] && input[i] != '$')
        i++;
    if (!(tmp = ft_substr(input, *start, i - *start)))
        return (NULL);
    *start = i;
    return (tmp);
}

static char *heredoc_append_env(int *start, char *input, t_exec_ctx *ctx)
{
    char        *tmp;
    int         i;
    t_env_var   *env;

    i = *start + 1;
    if (!input[i] || !is_valid_env_var_char(input[i]))
        return (heredoc_expand_dollar(start, input, ctx));
    while (input[i] && is_valid_env_var_char(input[i]))
        i++;
    if (!(tmp = ft_substr(input, *start + 1, i - *start - 1)))
        return (NULL);
    env = get_env_var(ctx->env_vars, tmp);
    free(tmp);
    *start = i;
    if (!env)
        return (ft_strdup("\0"));
    return (ft_strdup(env->value));
}

static char *heredoc_expand_input(char *input, t_exec_ctx *ctx)
{
    char    *tmp;
    char    *res;
    int     i;
    int     len;

    i = 0;
    len = ft_strlen(input);
    if (!(res = ft_strdup("")))
        return (NULL);
    while (i < len)
    {
        if (input[i] == '$')
            tmp = heredoc_append_env(&i, input, ctx);
        else
            tmp = heredoc_append_word(&i, input);
        if (!tmp)
            return (NULL);
        if (!(res = ft_strappend(res, tmp)))
            return (NULL);
        free(tmp);
    }
    free(input);
    return (res);
}

int heredoc_write_input(int mode, int tmp_file, char *input, t_exec_ctx *ctx)
{
    char    *output;

    if (!(output = ft_strdup(input)))
        return (0);
    if (mode == 2)
    {
        if (!(output = heredoc_expand_input(output, ctx)))
            return (0);
    }
    write(tmp_file, output, ft_strlen(output));
	write(tmp_file, "\n", 1);
    free(output);
    return (1);
}
