/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:25:49 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/14 09:54:22 by jkovacev         ###   ########.fr       */
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
	EXIT_STATUS_TOKEN,
	EXPANSION_TOKEN
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
}	t_token_context;

char	peek(t_token_context *context);
char	advance(t_token_context *context);
bool	match(char expected_char, t_token_context *context);
bool	add_token(t_token_context *context, t_token_type type);
t_list	*tokenize(char *s);
void	delete_token(void *t);
void	print(void *t); // delete later
bool	read_expansion(t_token_context *context);

#endif