/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: culbrich <culbrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:43:09 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/28 20:43:09 by culbrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

static char *heredoc_append_word(int *start, char *input)
{
    char    *tmp;
    int     i;

    i = *start;
    while (input[i] && input[i] != '$')
        i++;
    if (!(tmp = ft_substr(input, *start, i - *start)))
        return (NULL);
    *start = i + 1;
    return (tmp);
}

static char *heredoc_append_env(int *start, char *input, t_list *env_vars)
{
    char        *tmp;
    int         i;
    t_env_var   *env;

    i = *start + 1;
    if (!input[i] || !is_valid_env_var_char(input[i]))
        return (ft_strdup("$"));
    while (input[i] && is_valid_env_var_char(input[i]))
        i++;
    if (!(tmp = ft_substr(input, *start + 1, i - *start)))
        return (NULL);
    env = get_env_var(env_vars, tmp);
    free(tmp);
    *start = i + 1;
    if (!env)
        return (ft_strdup("\0"));
    return (ft_strdup(env->value));
}

static int  heredoc_expand_input(char **input, t_list *env_vars)
{
    char    *tmp;
    char    *res;
    int     i;
    int     len;

    i = 0;
    len = ft_strlen(*input);
    if (!(res = ft_strdup("")))
        return (0);
    while (i < len)
    {
        if (*input[i] == '$')
            tmp = heredoc_append_env(&i, *input, env_vars);
        else
            tmp = heredoc_append_word(&i, *input);
        if (!tmp)
            return (0);
        if (!(res = ft_strappend(res, tmp)))
            return (0);
        free(tmp);
    }
    free(*input);
    *input = res;
    return (1);
}

int heredoc_write_input(int mode, int tmp_file, char *input, t_list *env_vars)
{
    char    *output;

    if (!(output = ft_strdup(input)))
        return (0);
    if (mode == 2)
    {
        if (!(heredoc_expand_input(&output, env_vars)))
            return (0);
    }
    write(tmp_file, output, ft_strlen(output));
	write(tmp_file, "\n", 1);
    free(output);
    return (1);
}
