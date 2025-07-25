/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_callbacks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 22:36:25 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/26 20:28:41 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	delete_assignment(void *content)
{
	t_assignment *assignment;

	assignment = (t_assignment *)content;
	free(assignment->key);
	free(assignment->value);
	free(assignment);
}

static void	delete_redirection(void *content)
{
	t_redirection *redirection;

	redirection = (t_redirection *)content;
	free(redirection);
}

void	delete_command(void *content)
{
	t_command *command;

	command = (t_command *)content;
	free(command->argv);
	ft_lstclear(&command->assignments, &delete_assignment);
	ft_lstclear(&command->redirections, &delete_redirection);
	free(command);
}