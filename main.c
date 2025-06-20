/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:24:34 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/20 19:14:41 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(void *t) // delete later
{
	t_token *token;

	token = (t_token *)t;
	printf("type: %d lexeme: %s\n", token->type, token->lexeme);
}

void	print_env_var(void *var) // delete later
{
	t_env_var *env_var;

	env_var = (t_env_var *)var;
	printf("key: %s value: %s\n", env_var->key, env_var->value);
}

static bool	eval_loop(t_list *env_vars)
{
    char 			*input;
	t_token_context	context;

	input = NULL;
	while (1)
	{
		free(input);
		input = readline("minishell$ ");
		if (!input)
			return (false);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			break ;
		}
		if (!*input)
			continue ;
		add_history(input);
		context = (t_token_context){ .line = input };
		if (!tokenize(&context))
		{
			ft_lstclear(&context.tokens, &delete_token);
			if (context.error)
				continue ;
			return (false);
		}
		if (!expand_variables(context.tokens, env_vars))
		{
			ft_lstclear(&context.tokens, &delete_token);
			return (false);
		}
		ft_lstiter(context.tokens, &print_token);
		ft_lstclear(&context.tokens, &delete_token);
	}
	return (true);
}

int main(int argc, char *argv[], char *envp[])
{
	t_list	*env_vars;

	(void)argc;
	(void)argv;
	env_vars = copy_env_vars(envp);
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
