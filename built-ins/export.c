/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: culbrich <culbrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:55:49 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/08 16:22:39 by culbrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

// currently doesn't work, tokens elements containing '=' are NULL
int	ft_export(char **tokens, t_list *ev)
{
	int		i;
	int		exit_code;
	char	**pair;

	i = 1;
	exit_code = 0;
	while (tokens[i])
	{
		pair = ft_get_pair(tokens[i], ev);
		if (pair && *pair)
			exit_code |= add_env_var(ev, pair[0], pair[1], 1);
		else
			exit_code = 1;
		ft_free_strarray(pair);
		i++;
	}
	return (exit_code);
}

/* takes a token containing env variables and duplicates key and value pair into a new array
/  new variables are only handled in case of assigment ('='). returns NULL on error
*/ 
char	**ft_get_pair(char *token, t_list *ev)
{
	char	**pair;

	pair = NULL;
	if (!ft_strchr(token, '='))
	{
		if (ft_getenv(ev, token))
		{
			pair = (char **)malloc(sizeof(char *) * 3);
			pair[0] = ft_strdup(token);
			pair[1] = ft_strdup(ft_getenv_v(ft_getenv(ev, token)));
			pair[2] = NULL;
		}
	}
	else
		pair = ft_split(token, '=');
	return (pair);
}