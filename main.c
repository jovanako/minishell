/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:24:34 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/17 13:06:02 by jkovacev         ###   ########.fr       */
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

static void	eval_loop()
{
    char 	*input;
	t_list	*tokens;

	input = NULL;
	while (1)
	{
		free(input);
		input = readline("minishell$ ");
		if (!input)
			exit(1);
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			break ;	
		}
		if (*input)
		{
			tokens = tokenize(input);
			if (!tokens)
				continue;
			ft_lstiter(tokens, &print_token);
			add_history(input);
		}
		ft_lstclear(&tokens, &delete_token);
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_list	*env_vars;

	(void)argc;
	(void)argv;
	env_vars = copy_env_vars(envp);
	if (!env_vars)
		return (1);
	ft_lstiter(env_vars, &print_env_var);
	eval_loop();
	ft_lstclear(&env_vars, &delete_env_var);
	return (0);
}
