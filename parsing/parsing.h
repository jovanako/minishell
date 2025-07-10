/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:03:01 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/10 18:22:43 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "../tokenizer/tokenizer.h"

typedef enum e_redirect_type
{
	INPUT_REDIRECT,
	OUTPUT_REDIRECT,
	APPEND_REDIRECT,
	HEREDOC_REDIRECT,
	UNKNOWN_REDIRECT
}	t_redirect_type;

typedef struct s_assignment
{
	char	*key;
	char	*value;
}	t_assignment;

typedef struct s_command
{
	t_list	*assignments;
	char	**argv;
	t_list	*redirections;
	pid_t	pid;
}	t_command;

typedef struct s_redirection
{
	t_redirect_type	type;
	char			*target;
}	t_redirection;

typedef struct s_parsing_context
{
	t_list	*tokens;
	t_list	*current;
	t_list	*commands;
	char	*error;
}	t_parsing_context;

bool	is_current_type(t_parsing_context *ctx, t_token_type token_type);
bool	is_at_end(t_parsing_context *ctx);
bool	p_match(t_parsing_context *ctx, t_token_type token_type);
t_token	*p_advance(t_parsing_context *ctx);
t_token	*get_current(t_parsing_context *ctx);
bool	parse_assignment_list(t_parsing_context *ctx, t_command *command);
bool 	parse_assignment(t_parsing_context *ctx, t_command *command);
bool 	parse_redirection_list(t_parsing_context *ctx, t_command *command);
bool	parse_redirection(t_parsing_context *ctx, t_command *command);
bool	parse_argv(t_parsing_context *ctx, t_command *command);
bool	parse(t_parsing_context *ctx);
void	delete_command(void *content);
#endif