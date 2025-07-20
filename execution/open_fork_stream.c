/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fork_stream.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:50:37 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/20 18:53:26 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
