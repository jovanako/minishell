/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:24:34 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/26 17:59:29 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_last_sig;

static bool	read_input(char **input)
{
	free(*input);
	ft_change_sigmode(SIG_INTERACTIVE);
	*input = readline("🐚" CYN BOLD "minishell$ " RESET UNBOLD);
	ft_change_sigmode(SIG_NONINTERACTIVE);
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
	t_token_context		*t_ctx;
	t_parsing_context	p_ctx;
	t_execution_context	e_ctx;

	input = NULL;
	e_ctx = (t_execution_context){ .exit = false };
	while (!e_ctx.exit)
	{
		if (!read_input(&input))
			return (false);
		t_ctx = tokenize(input);
		if (!t_ctx)
			return(false);
		if (t_ctx->error)
			continue;
		if (!expand(t_ctx, env_vars))
			return (false);
		p_ctx = (t_parsing_context){ .tokens = t_ctx->tokens,
			.current = t_ctx->tokens, .commands = NULL };
		if (!parse(&p_ctx))
			return (false);
		e_ctx.commands = p_ctx.commands;
		e_ctx.env_vars = env_vars;
		if (!execute(&e_ctx))
			return (false);
		// free contexts	
		ft_lstclear(&(t_ctx->tokens), &delete_token);
		ft_lstclear(&(p_ctx.commands), &delete_command);
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
		printf("exit\n");
		ft_lstclear(&env_vars, &delete_env_var);
		return (1);
	}
	ft_lstclear(&env_vars, &delete_env_var);
	return (0);
}

