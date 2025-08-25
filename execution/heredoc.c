/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:38:32 by culbrich          #+#    #+#             */
/*   Updated: 2025/08/25 19:39:18 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../err_printf/err_printf.h"
#include "../minishell.h"

/*	returns 0 on invalid input
/	returns 1 on valid quotes
/	returns 2 on unquoted
*/
static int	hd_quoted_delimiter(t_redirection *redir, char **delimiter)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (redir->target[i])
	{
		if (!hd_quoted_dl_loop(redir, delimiter, &i, &quote))
			return (0);
	}
	if (quote != 0)
		return (1);
	else
	{
		free(*delimiter);
		*delimiter = ft_strdup(redir->target);
		if (!(*delimiter))
			return (0);
		return (2);
	}
}

static int	hd_loop(const int tmp_file, char *dl, int mode, t_exec_ctx *ctx)
{
	char	*input;
	int		i;

	input = NULL;
	i = 1;
	while (1)
	{
		free(input);
		ft_change_sigmode(SIG_HEREDOC);
		input = readline("> ");
		ft_change_sigmode(SIG_NONINTERACTIVE);
		if (!input)
		{
			err_printf("-minishell: warning: here-document at line "
				"%d delimited by end-of-file (wanted '%s')\n", i, dl);
			break ;
		}
		if (ft_strcmp(input, dl) == 0 || g_last_sig == SIGINT)
			break ;
		if (!(heredoc_write_input(mode, tmp_file, input, ctx)))
			return (0);
		i++;
	}
	return (1);
}

static int	open_hd_redir_helper(char *delimiter, t_fork_streams *f_s)
{
	int	tmp_file;

	if (g_last_sig == SIGINT)
	{
		rl_done = 0;
		tmp_file = open(TMP_FILE, O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	}
	else
		tmp_file = open(TMP_FILE, O_RDONLY);
	if (!tmp_file)
		return (close_heredoc(delimiter, -1));
	f_s->input_fd = tmp_file;
	return (close_heredoc(delimiter, f_s->input_fd));
}

int	open_hd_redir(t_fork_streams *f_s, t_redirection *redir, t_exec_ctx *ctx)
{
	char	*delimiter;
	int		mode;
	int		tmp_file;

	delimiter = ft_strdup("");
	if (!delimiter)
		return (close_heredoc(delimiter, -1));
	mode = hd_quoted_delimiter(redir, &delimiter);
	if (mode == 0)
		return (close_heredoc(delimiter, -1));
	tmp_file = open(TMP_FILE, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (!tmp_file)
		return (close_heredoc(delimiter, -1));
	if (!(hd_loop(tmp_file, delimiter, mode, ctx)))
	{
		close(tmp_file);
		return (close_heredoc(delimiter, -1));
	}
	close(tmp_file);
	return (open_hd_redir_helper(delimiter, f_s));
}
