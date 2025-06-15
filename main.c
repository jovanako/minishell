/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:24:34 by jkovacev          #+#    #+#             */
/*   Updated: 2025/06/15 13:04:47 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print(void *t) // delete later
{
	t_token *token;

	token = (t_token *)t;
	printf("type: %d lexeme: %s\n", token->type, token->lexeme);
}

int main(void)
{
    char 	*input;
	t_list	*tokens;

	input = NULL;
	while (1)
	{
		free(input);
		input = readline("minishell$ ");
		if (!input)
			return (1); // check exit status
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			break ;	
		}
		if (*input)
		{
			tokens = tokenize(input);
			ft_lstiter(tokens, &print);
			add_history(input);
		}
		ft_lstclear(&tokens, &delete_token);
	}
	return (0);
}
