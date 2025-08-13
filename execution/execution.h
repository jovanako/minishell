/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:24:40 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/29 20:50:01 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

/*---------------------------------------------------*/
/*---------------------INCLUDES----------------------*/
/*---------------------------------------------------*/

# include "../libft/libft.h"
# include "../parsing/parsing.h"
# include "../utils/utils.h"
# include <stdbool.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

/*---------------------------------------------------*/
/*----------------------STRUCTS----------------------*/
/*---------------------------------------------------*/

typedef struct s_fork_streams
{
	int	input_fd;
	int	output_fd;
}	t_fork_streams;

typedef struct s_execution_context
{
	t_list	*commands;
	t_list	*env_vars;
	bool	exit;
	bool	error;
	int		status;
}	t_exec_ctx;

/*---------------------------------------------------*/
/*---------------------FUNCTIONS---------------------*/
/*---------------------------------------------------*/

//	cmdpath
char		*ft_cmdpath(t_list *lst, char *cmd);

//	execution_built_in
bool		fork_built_in(t_exec_ctx *ctx, t_command *cmd, t_fork_streams *s);
bool		is_built_in(char *cmd_name);
bool		is_special_built_in(t_list *commands);
int			exec_built_in(t_exec_ctx *ctx, t_command *cmd);

//	execution_context
t_exec_ctx	*new_exec_ctx(t_parse_ctx *p_ctx, t_list *env_vars, int status);
void		*free_exec_ctx(t_exec_ctx *ctx);

//	execution_execve
bool		fork_execve(t_command *cmd, t_list *ev, t_fork_streams *fs);

//	execution_helpers
t_list		*resolve_fork_ev(t_list *assignments, t_list *env_vars);
char		**ev_list_to_arr(t_list *env_vars);
bool		check_can_read(char *target);
int			wait_for_children(t_list *commands);

//	execution_no_command
int			handle_no_command(t_command *cmd, t_list *env_vars);

//	execution
t_exec_ctx	*execute(t_parse_ctx *p_ctx, t_list *env_vars, int status);

//	open_fork_stream
int			open_input_redir(t_fork_streams *fs, t_redirection *redir);
int			open_output_redir(t_fork_streams *fs, t_redirection *redir);
int			open_append_redir(t_fork_streams *fs, t_redirection *redir);

//	heredoc
int			open_hd_redir(t_fork_streams *fs,
				t_redirection *rd, t_exec_ctx *ctx);

//	heredoc_expanstion
int			close_heredoc(char *delimiter, int error);
int			heredoc_write_input(int mode, int tmp_file,
				char *input, t_exec_ctx *ctx);

//	heredoc_helpers
char		*heredoc_expand_dollar(int *start, char *input, t_exec_ctx *ctx);
int			heredoc_event_hook(void);
int			hd_quoted_dl_loop(t_redirection *redir, char **dl,
				int *start, char *q);

#endif
