/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:24:34 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/07 19:32:46 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	read_input(char **input)
{
	free(*input);
	ft_change_sigmode(1);
	*input = readline("🐚minishell$ ");
	if (!*input)
		return (false);
	add_history(*input);
	return (true);
}

static bool	expand(t_token_context *ctx, t_list *env_vars)
{
	if (!expand_variables(ctx->tokens, env_vars))
	{
		ft_lstclear(&(ctx->tokens), &delete_token);
		return (false);
	}
	return (true);
}

static bool	eval_loop(t_list *env_vars)
{
    char 				*input;
	t_token_context		token_context;
	t_parsing_context	parsing_context;

	input = NULL;
	while (1)
	{
		if (!read_input(&input))
			return (false);
		token_context = (t_token_context){ .line = input };
		if (!tokenize(&token_context))
		{
			ft_lstclear(&token_context.tokens, &delete_token);
			if (token_context.error)
				continue ;
			return (false);
		}
		if (!expand(&token_context, env_vars))
			return (false);
		parsing_context = (t_parsing_context){ .tokens = token_context.tokens, .current = token_context.tokens, .syntax_tree = NULL };
		if (!parse(&parsing_context))
			return (false);
		ft_change_sigmode(0);
		if (!execute(parsing_context.syntax_tree, env_vars))
			return (false);
		ft_lstclear(&(token_context.tokens), &delete_token);
		ft_lstclear(&(parsing_context.syntax_tree), &delete_command);
	}
	return (true);
}

int main(int argc, char *argv[], char *envp[])
{
	t_list	*env_vars;

	(void)argc;
	(void)argv;
	env_vars = create_env_vars(envp);
	if (!env_vars)
		return (1);
	if (!eval_loop(env_vars))
	{
		ft_lstclear(&env_vars, &delete_env_var);
		return (1);
	}
	ft_lstclear(&env_vars, &delete_env_var);
	return (0);
}

