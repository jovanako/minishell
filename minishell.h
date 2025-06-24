/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:25:49 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/24 21:45:50 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

typedef enum e_token_type
{
	INPUT_REDIR_TOKEN,
	OUTPUT_REDIR_TOKEN,
	HEREDOC_TOKEN,
	APPEND_TOKEN,
	PIPE_TOKEN,
	NULL_TERMINATOR_TOKEN,
	ASSIGNMENT_TOKEN,
	WORD_TOKEN
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*lexeme;
}	t_token;

typedef struct s_token_context
{
	int		start;
	int		current;
	char	*line;
	t_list	*tokens;
	char	*error;
}	t_token_context;

typedef struct s_env_var
{
	char	*key;
	char	*value;
}	t_env_var;

typedef struct s_expansion_context
{
	int		current;
	char	*lexeme;
	char	*result;
}	t_expansion_context;

//tokenization
char	peek(t_token_context *context);
char	advance(t_token_context *context);
bool	match(char expected_char, t_token_context *context);
bool	is_valid_identifier(t_token_context *ctx);
bool	add_token(t_token_context *context, t_token_type type);
bool	tokenize(t_token_context *context);
void	delete_token(void *t);
bool	read_word(t_token_context *context);
bool	read_less_than(t_token_context *context);
bool	read_greater_than(t_token_context *context);
bool	read_heredoc_delimiter(t_token_context *context);
//expansion
t_list	*copy_env_vars(char *envp[]);
bool	get_env_value(void *content, void *var_key);
bool	append_slice(t_expansion_context *ctx, char *end);
bool	append_value(t_expansion_context *ctx, char *var_value);
void	delete_env_var(void *var);
bool	expand_variables(t_list *tokens, t_list *env_vars);
bool	is_valid_env_var_char(char c);
bool	is_unquoted(char c);
bool	is_quote(char c);
bool	handle_dollar(t_expansion_context *ctx, t_list *env_vars, int *i);
bool	slice_single_quoted(t_expansion_context *ctx);
bool	slice_double_quoted(t_expansion_context *ctx, t_list *env_vars);
bool	slice_unquoted(t_expansion_context *ctx, t_list *env_vars);
void	print_token(void *t); // delete later
#endif