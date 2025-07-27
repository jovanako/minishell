/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:24:34 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/27 14:27:43 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_last_sig;

static void clean_up(t_token_context **t, t_parse_ctx **p, t_exec_ctx **e)
{
	t = free_token_ctx(*t);
	p = free_parsing_ctx(*p);
	e = free_exec_ctx(*e);
}

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
	if (!ctx)
		return (false);
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
	t_parse_ctx			*p_ctx;
	t_exec_ctx			*e_ctx;
	bool				exit;

	input = NULL;
	exit = false;
	while (!exit)
	{
		read_input(&input);
		t_ctx = tokenize(input);
		if (t_ctx && t_ctx->error)
			continue ;
		expand(t_ctx, env_vars);
		p_ctx = parse(t_ctx);
		if (p_ctx && p_ctx->error)
			continue ;
		e_ctx = execute(p_ctx, env_vars);
		if (!e_ctx)
			return (false);
		if (e_ctx->error)
			continue ;
		exit = e_ctx->exit;
		clean_up(&t_ctx, &p_ctx, &e_ctx);
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

