/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:03:01 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/25 14:12:14 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/*---------------------------------------------------*/
/*---------------------INCLUDES----------------------*/
/*---------------------------------------------------*/

# include "../tokenizer/tokenizer.h"

/*---------------------------------------------------*/
/*----------------------STRUCTS----------------------*/
/*---------------------------------------------------*/

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

typedef struct s_parse_ctx
{
	t_list	*tokens;
	t_list	*current;
	t_list	*commands;
	bool	error;
}	t_parse_ctx;

/*---------------------------------------------------*/
/*---------------------FUNCTIONS---------------------*/
/*---------------------------------------------------*/

bool		is_current_type(t_parse_ctx *ctx, t_token_type token_type);
bool		is_at_end(t_parse_ctx *ctx);
bool		p_match(t_parse_ctx *ctx, t_token_type token_type);
t_token		*p_advance(t_parse_ctx *ctx);
t_token		*get_current(t_parse_ctx *ctx);
bool		parse_assignment_list(t_parse_ctx *ctx, t_command *command);
bool		parse_assignment(t_parse_ctx *ctx, t_command *command);
bool		parse_redirection_list(t_parse_ctx *ctx, t_command *command);
bool		parse_argv(t_parse_ctx *ctx, t_command *command);
t_parse_ctx	*parse(t_token_context *t_ctx);
t_parse_ctx	*new_parsing_ctx(t_token_context *t_ctx);
void		delete_command(void *content);
void		deep_delete_command(void *content);
void		*free_parsing_ctx(t_parse_ctx *ctx);
#endif
