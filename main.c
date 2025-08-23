/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:24:34 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/23 19:47:34 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_last_sig;

static int	clean_up(t_ctx_holder *ctx_holder)
{
	int	ret;

	ret = ctx_holder->status;
	ctx_holder->t_ctx = free_token_ctx(ctx_holder->t_ctx);
	ctx_holder->p_ctx = free_parsing_ctx(ctx_holder->p_ctx);
	ctx_holder->e_ctx = free_exec_ctx(ctx_holder->e_ctx);
	return (ret);
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

static bool	eval(t_ctx_holder *ctx_holder, char *input, t_list **env_vars)
{
	ctx_holder->t_ctx = tokenize(input);
	if (ctx_holder->t_ctx && ctx_holder->t_ctx->error)
	{
		ctx_holder->status = 2;
		return (true);
	}
	expand(ctx_holder->t_ctx, *env_vars, ctx_holder->status);
	if (ft_lstsize(ctx_holder->t_ctx->tokens) == 1)
		return (true);
	ctx_holder->p_ctx = parse(ctx_holder->t_ctx);
	if (ctx_holder->p_ctx && ctx_holder->p_ctx->error)
	{
		ctx_holder->status = 2;
		return (true);
	}
	ctx_holder->e_ctx = execute(ctx_holder->p_ctx,
			env_vars, ctx_holder->status);
	if (!ctx_holder->e_ctx)
		return (false);
	ctx_holder->exit = ctx_holder->e_ctx->exit;
	ctx_holder->status = ft_get_last_sig_exit(ctx_holder->e_ctx->status);
	return (true);
}

static int	eval_loop(t_list **env_vars)
{
	char			*input;
	t_ctx_holder	ctx_holder;
	int				ret;

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
		ret = clean_up(&ctx_holder);
	}
	return (ret);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_list	*env_vars;
	int		ret;

	(void)argc;
	(void)argv;
	env_vars = create_env_vars(envp);
	if (!env_vars)
		return (1);
	ret = eval_loop(&env_vars);
	ft_lstclear(&env_vars, &delete_env_var);
	return (ret);
}
