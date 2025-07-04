/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_no_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:08:33 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/04 22:33:51 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../utils/utils.h"

static int	handle_assignments(t_list *assignments, t_list *ev)
{
	t_assignment	*assignment;
	t_env_var		*new_var;
	t_list			*node;

	while (assignments)
	{
		assignment = assignments->content;		
		new_var = malloc(sizeof(t_env_var));
		if (!new_var)
			return (1);
		new_var->exported = false;
		new_var->key = ft_strcpy(assignment->key);
		if (!new_var->key)
			return (free_ev_and_return(new_var, 1));
		new_var->value = ft_strcpy(assignment->value);
		if (!new_var->value)
			return (free_ev_and_return(new_var, 1));
		node = ft_lstnew(new_var);
		if (!node)
			return (free_ev_and_return(new_var, 1));
		ft_lstadd_back(&ev, node);
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
			fd = open(redirection->target, O_CREAT | O_WRONLY, rights_flags);
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
