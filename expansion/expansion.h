/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 08:36:15 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/19 15:25:08 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

/*---------------------------------------------------*/
/*---------------------INCLUDES----------------------*/
/*---------------------------------------------------*/

# include "../libft/libft.h"
# include "../tokenizer/tokenizer.h"
# include "../utils/utils.h"
# include "../env_vars/env_vars.h"

/*---------------------------------------------------*/
/*----------------------STRUCTS----------------------*/
/*---------------------------------------------------*/

typedef struct s_expansion_context
{
	int		current;
	char	*lexeme;
	char	*result;
	int		exit_status;
}	t_expansion_context;

/*---------------------------------------------------*/
/*---------------------FUNCTIONS---------------------*/
/*---------------------------------------------------*/

// expansion
bool	expand_variables(t_list *tokens, t_list *env_vars, int status);
bool	handle_exit_expand(t_expansion_context *ctx, int *i);
bool	expand(t_token_context *ctx, t_list *env_vars, int status);

// slicing
bool	append_slice(t_expansion_context *ctx, char *end);
bool	slice_single_quoted(t_expansion_context *ctx);
bool	slice_double_quoted(t_expansion_context *ctx, t_list *env_vars);
bool	slice_unquoted(t_expansion_context *ctx, t_list *env_vars);

// expansion_helpers
bool				append_value(t_expansion_context *ctx, char *var_value);
char				*extract_var_key(t_expansion_context *ctx, int *start);
bool				is_unquoted(char c);
bool				is_quote(char c);
bool				handle_dollar(t_expansion_context *ctx, t_list *env_vars, int *i);
t_expansion_context	*new_e_ctx(char *lexeme, int status);
bool				*free_expansion_ctx(t_expansion_context *ctx);

// cleanup
// bool	free_result_and_return(t_expansion_context *ctx);

#endif
