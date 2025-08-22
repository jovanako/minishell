/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fork_stream.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:50:37 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/22 20:43:42 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"
#include "../err_printf/err_printf.h"

int	open_input_redir(t_fork_streams *fork_streams, t_redirection *redir)
{
	if (fork_streams->input_fd != STDIN_FILENO)
		close(fork_streams->input_fd);
	fork_streams->input_fd = open(redir->target, O_RDONLY);
	if (fork_streams->input_fd == -1)
	{
		err_printf("minishell: %s: %s\n", redir->target, strerror(errno));
		return (-1);
	}
	return (fork_streams->input_fd);
}

int	open_output_redir(t_fork_streams *fork_streams, t_redirection *redir)
{
	if (fork_streams->output_fd != STDOUT_FILENO)
		close(fork_streams->output_fd);
	fork_streams->output_fd = open(redir->target, O_CREAT
			| O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fork_streams->output_fd == -1)
	{
		err_printf("minishell: %s: %s\n", redir->target, strerror(errno));
		return (-1);
	}
	return (fork_streams->output_fd);
}

int	open_append_redir(t_fork_streams *fork_streams, t_redirection *redir)
{
	if (fork_streams->output_fd != STDOUT_FILENO)
		close(fork_streams->output_fd);
	fork_streams->output_fd = open(redir->target, O_CREAT
			| O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fork_streams->output_fd == -1)
	{
		err_printf("minishell: %s: %s\n", redir->target, strerror(errno));
		return (-1);
	}
	return (fork_streams->output_fd);
}
