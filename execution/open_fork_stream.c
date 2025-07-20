/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fork_stream.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:50:37 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/08 12:51:09 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

int	open_input_redir(t_fork_streams *fork_streams, t_redirection *redir)
{
	if (fork_streams->input_fd != STDIN_FILENO)
		close(fork_streams->input_fd);
	fork_streams->input_fd = open(redir->target, O_RDONLY);
	return (fork_streams->input_fd);
}

int	open_output_redir(t_fork_streams *fork_streams, t_redirection *redir)
{
	if (fork_streams->output_fd != STDOUT_FILENO)
		close(fork_streams->output_fd);
	fork_streams->output_fd = open(redir->target, O_CREAT 
		| O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	return (fork_streams->output_fd);
}

int	open_append_redir(t_fork_streams *fork_streams, t_redirection *redir)
{
	if (fork_streams->output_fd != STDOUT_FILENO)
		close(fork_streams->output_fd);
	fork_streams->output_fd = open(redir->target, O_CREAT 
		| O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	return (fork_streams->output_fd);
}

int	open_heredoc_redir(t_fork_streams *fork_streams, t_redirection *redir)
{
	char	*input;
	int		tmp_file;

	tmp_file = open(".tmp", O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (!tmp_file)
		return 0;
	input = NULL;
	while (1)
	{
		free(input);
		input = readline("> ");
		if (ft_strcmp(input, redir->target) == 0)
			break;
		write(tmp_file, input, ft_strlen(input));
		write(tmp_file, "\n", 1);
    }
	close(tmp_file);
	tmp_file = open(".tmp", O_RDONLY);
	if (!tmp_file)
		return 0;
	fork_streams->input_fd = tmp_file;
	return(fork_streams->input_fd);
}