/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 08:36:15 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/03 09:49:13 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

#include "../libft/libft.h"
#include "../tokenizer/tokenizer.h"
#include "../utils/utils.h"

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

bool	append_slice(t_expansion_context *ctx, char *end);
bool	append_value(t_expansion_context *ctx, char *var_value);
bool	handle_dollar(t_expansion_context *ctx, t_list *env_vars, int *i);
bool	slice_single_quoted(t_expansion_context *ctx);
bool	slice_double_quoted(t_expansion_context *ctx, t_list *env_vars);
bool	slice_unquoted(t_expansion_context *ctx, t_list *env_vars);
bool	is_valid_env_var_char(char c);
bool	is_unquoted(char c);
bool	is_quote(char c);
bool	expand_variables(t_list *tokens, t_list *env_vars);
#endif