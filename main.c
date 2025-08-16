/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:24:34 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/31 21:12:52 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_last_sig;

static bool	clean_up(t_ctx_holder *ctx_holder)
{
	ctx_holder->t_ctx = free_token_ctx(ctx_holder->t_ctx);
	ctx_holder->p_ctx = free_parsing_ctx(ctx_holder->p_ctx);
	ctx_holder->e_ctx = free_exec_ctx(ctx_holder->e_ctx);
	return (false);
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

static bool	eval(t_ctx_holder *ctx_holder, char *input, t_list *env_vars)
{
	ctx_holder->t_ctx = tokenize(input);
	if (ctx_holder->t_ctx && ctx_holder->t_ctx->error)
		return (true);
	expand(ctx_holder->t_ctx, env_vars, ctx_holder->status);
	ctx_holder->p_ctx = parse(ctx_holder->t_ctx);
	if (ctx_holder->p_ctx && ctx_holder->p_ctx->error)
		return (true);
	ctx_holder->e_ctx = execute(ctx_holder->p_ctx,
			env_vars, ctx_holder->status);
	if (!ctx_holder->e_ctx)
		return (false);
	if (ctx_holder->e_ctx->error)
		return (true);
	ctx_holder->exit = ctx_holder->e_ctx->exit;
	ctx_holder->status = ft_get_last_sig_exit(ctx_holder->e_ctx->status);
	return (true);
}

static bool	eval_loop(t_list *env_vars)
{
	char			*input;
	t_ctx_holder	ctx_holder;

	input = NULL;
	ctx_holder.exit = false;
	ctx_holder.status = 0;
	ctx_holder.t_ctx = NULL;
	ctx_holder.p_ctx = NULL;
	ctx_holder.e_ctx = NULL;
	while (!ctx_holder.exit)
	{
		read_input(&input);
		ctx_holder.status = ft_get_last_sig_exit(ctx_holder.status);
		if (!input)
			ctx_holder.exit = ft_exit_sigeof();
		else if (*input)
		{
			if (!eval(&ctx_holder, input, env_vars))
				return (clean_up(&ctx_holder));
		}
		clean_up(&ctx_holder);
	}
	return (true);
}

int	main(int argc, char *argv[], char *envp[])
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
