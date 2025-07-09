/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_no_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:08:33 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/07 08:47:26 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../utils/utils.h"

static int	handle_assignments(t_list *assignments, t_list *ev)
{
	t_assignment	*assignment;
	char			*key;
	char			*val;

	key = NULL;
	val = NULL;
	while (assignments)
	{
		assignment = assignments->content;		
		key = ft_strcpy(assignment->key);
		val = ft_strcpy(assignment->value);
		if (!key || !val || !add_env_var(&ev, key, val, false))
		{
			free(key);
			free(val);
			return (1);
		}
		assignments = assignments->next;
	}
	return (0);
}

static int	handle_redirections(t_list	*redirections)
{
	t_redirection	*redirection;
	int				fd;
	int 			rights_flags;

	rights_flags = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	while (redirections)
	{
		redirection = redirections->content;
		if (redirection->type == OUTPUT_REDIRECT)
		{
			fd = open(redirection->target, O_CREAT 
				| O_WRONLY | O_TRUNC, rights_flags);
			close(fd);
		}	
		else if (redirection->type == APPEND_REDIRECT)
		{
			fd = open(redirection->target, O_CREAT 
				| O_WRONLY | O_APPEND, rights_flags);
			close(fd);
		} 
		redirections = redirections->next;
	}
	return (0);
}

int	handle_no_command(t_command *cmd, t_list *env_vars)
{
	if (cmd->assignments)
		return (handle_assignments(cmd->assignments, env_vars));
	if (cmd->redirections)
		return (handle_redirections(cmd->redirections));
	return (0);
}
