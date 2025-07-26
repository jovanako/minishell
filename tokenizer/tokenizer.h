/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:34:56 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/26 18:27:14 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

/*---------------------------------------------------*/
/*---------------------INCLUDES----------------------*/
/*---------------------------------------------------*/

#include "../libft/libft.h"
#include <stdio.h>

/*---------------------------------------------------*/
/*----------------------STRUCTS----------------------*/
/*---------------------------------------------------*/

typedef enum e_token_type
{
	INPUT_REDIR_TOKEN,
	OUTPUT_REDIR_TOKEN,
	HEREDOC_TOKEN,
	APPEND_TOKEN,
	PIPE_TOKEN,
	NULL_TERMINATOR_TOKEN,
	ASSIGNMENT_TOKEN,
	WORD_TOKEN,
	UNDEFINED,
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
	bool	error;
}	t_token_context;

/*---------------------------------------------------*/
/*---------------------FUNCTIONS---------------------*/
/*---------------------------------------------------*/

char			peek(t_token_context *context);
char			advance(t_token_context *context);
bool			match(char expected_char, t_token_context *context);
bool			is_valid_identifier(t_token_context *ctx);
bool			is_previous_token(t_token_context *ctx, t_token_type type);
bool			add_token(t_token_context *context, t_token_type type);
t_token_context *new_ctx(char *input);
t_token_context	*tokenize(char *input);
void			*free_token_ctx(t_token_context *ctx);
void			delete_token(void *t);
bool			read_word(t_token_context *context);
bool			read_heredoc_delimiter(t_token_context *context);

#endif