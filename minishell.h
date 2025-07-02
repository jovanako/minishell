/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:25:49 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/02 17:22:38 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include "tokenizer/tokenizer.h"
#include "parsing/parsing.h"
#include "execution/execution.h"

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
#endif