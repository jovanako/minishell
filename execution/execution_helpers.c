/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:32:00 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/07 10:46:52 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**ev_list_to_arr(t_list *env_vars)
{
	int			len;
	int			i;
	char		**result;
	t_env_var	*var;
	char		*str_var;

	i = 0;
	len = ft_lstsize(env_vars);
	result = malloc((len + 1) * sizeof(char *));
	if (!result)
		return NULL;
	while (env_vars)
	{
		var = (t_env_var *)env_vars->content;
		str_var = ft_strjoin(var->key, "=");
		// TODO check ft_strjoin success and free result and elements on fail
		str_var = ft_strjoin(str_var, var->value);
		// TODO check ft_strjoin success and free result and elements on fail
		result[i++] = str_var;
		env_vars = env_vars->next;
	}
	result[i] = NULL;
	return (result);
}

t_list	*resolve_assignments(t_list *assignments, t_list *env_vars)
{
	// TODO create a copy of env_vars and apply assignments to the copy
	(void)assignments;
	return (env_vars); // temp impl for testing
}

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
