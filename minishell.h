/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:25:49 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/15 19:51:44 by jkovacev         ###   ########.fr       */
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
	EQUALS_TOKEN,
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

char	peek(t_token_context *context);
char	advance(t_token_context *context);
bool	match(char expected_char, t_token_context *context);
bool	add_token(t_token_context *context, t_token_type type);
t_list	*tokenize(char *s);
void	delete_token(void *t);
bool	read_word(t_token_context *context);
bool	read_less_than(t_token_context *context);
bool	read_greater_than(t_token_context *context);
bool	read_heredoc_delimiter(t_token_context *context);
t_list	*copy_env_vars(char *envp[]);
void	print_token(void *t); // delete later
#endif