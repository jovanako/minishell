/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: culbrich <culbrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:38:32 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/28 15:42:53 by culbrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

static int	heredoc_append_slice(t_redirection *redir, char **delimiter, int start, int end)
{
	char	*slice;

	if (!(slice = ft_substr(redir->target, start, end - start)))
		return (0);
	if (!(*delimiter = ft_strappend(*delimiter, slice)))
	{
		free(slice);
		return (0);
	}
	free(slice);
	return (1);
}

static int	heredoc_find_next_quote(t_redirection *redir, char **delimiter, char quote, int *start)
{
	int	i;

	i = *start;
	while (redir->target[i] != quote)
	{
		if (!redir->target[i++])
			return (0); // invalid input
	}
	if (!(heredoc_append_slice(redir, delimiter, *start, i)))
		return (0); // malloc error
	*start = i + 1;
	return (1);
}

/*	returns 0 on invalid input
/	returns 1 on valid quotes
/	returns 2 on unquoted
*/
static int	heredoc_quoted_delimiter(t_redirection *redir, char **delimiter)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (redir->target[i])
	{
		if (redir->target[i] == '\'' || redir->target[i] == '\"')
		{
			quote = redir->target[i++];
			if (!(heredoc_find_next_quote(redir, delimiter, quote, &i)))
				return (0); // return heredoc_find_next_quote error
		}
		else
		{
			if (!(heredoc_append_slice(redir, delimiter, i, i + 1)))
				return (0);
			i++;
		}
	}
	if (quote != 0)
		return (1);
	else
	{
		if (!(*delimiter = ft_strdup(redir->target)))
			return (0); // malloc error
		return (2);
	}
}

static int	heredoc_loop(const int tmp_file, char *delimiter, int mode, t_list *env_vars)
{
	char	*input;
	int		i;

	input = NULL;
	i = 1;
	while (1)
	{
		free(input);
		rl_event_hook = ft_sig_heredoc;
		input = readline("> ");
		rl_event_hook = 0;
		if (!input)
		{
			printf("-minishell: warning: here-document at line %d delimited by end-of-file (wanted '%s')\n", i, delimiter);
			break;
		}
		if (ft_strcmp(input, delimiter) == 0 || g_last_sig == SIGINT)
			break;
		if (!(heredoc_write_input(mode, tmp_file, input, env_vars)))
			return (0);
		i++;
    }
	return (1);
}

int	open_heredoc_redir(t_fork_streams *fork_streams, t_redirection *redir, t_list *env_vars)
{
	char	*delimiter;
	int		mode;
	int		tmp_file;

	if (!(delimiter = ft_strdup("")))
		return (close_heredoc(delimiter, -1));
	if (!(mode = heredoc_quoted_delimiter(redir, &delimiter)))
		return (close_heredoc(delimiter, -1));
	tmp_file = open("/tmp/minishell.tmp", O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (!tmp_file)
		return (close_heredoc(delimiter, -1));
	if (!(heredoc_loop(tmp_file, delimiter, mode, env_vars)))
		return (close_heredoc(delimiter, -1));
	close(tmp_file);
	if (g_last_sig == SIGINT)
	{
		rl_done = 0;
		tmp_file = open("/tmp/minishell.tmp", O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	}
	else
		tmp_file = open("/tmp/minishell.tmp", O_RDONLY);
	if (!tmp_file)
		return (close_heredoc(delimiter, -1));
	fork_streams->input_fd = tmp_file;
	return (close_heredoc(delimiter, fork_streams->input_fd));
}
