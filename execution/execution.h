/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:24:40 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/07 09:01:52 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "../libft/libft.h"
#include "../parsing/parsing.h"
#include "../utils/utils.h"
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

typedef enum e_built_in_name 
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	INVALID
}	t_built_in_name;

typedef struct s_fork_streams
{
	int	input_fd;
	int	output_fd;
}	t_fork_streams;

bool 			execute(t_list* commands, t_list* env_vars);
bool			fork_execve(t_command *cmd, t_list *ev, t_fork_streams *s);
bool			fork_built_in(t_command *command, t_list *ev, t_fork_streams *s);
int				open_input_redir(t_fork_streams *fork_streams, t_redirection *redir);
int				open_output_redir(t_fork_streams *fork_streams, t_redirection *redir);
int				open_append_redir(t_fork_streams *fork_streams, t_redirection *redir);
t_built_in_name	find_built_in_name(char *cmd_name);
t_list			*resolve_assignments(t_list *assignments, t_list *env_vars);
bool			is_built_in(char *cmd_name);
bool			is_special_built_in(t_list *commands);
int				exec_built_in(t_built_in_name built_in, char *av[], t_list *ev);
char			**ev_list_to_arr(t_list *env_vars);
int				handle_no_command(t_command *cmd, t_list *env_vars);
#endif