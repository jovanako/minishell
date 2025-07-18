/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:55:49 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/11 20:26:16 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

/*	adds one or more given env vals to global scope
/	creates a new env val if needed
/	returns 0 if all tokens were exported, 1 if at least one failed
*/
int	ft_export(char **tokens, t_list *ev, t_list *assignments)
{
	int		i;
	int		exit_code;
	char	**pair;

	(void)assignments; // remove after impl
	i = 1;
	exit_code = 0;
	pair = (char **)malloc(sizeof(char *) * 2);
	if (!pair)
		return (1);
	while (tokens[i])
	{
		ft_get_pair(pair, tokens[i], ev);
		if (pair[0])
		{
			if (!add_env_var(&ev, pair[0], pair[1], 1))
			{
				exit_code = 1;
				if (pair[0])
					free(pair[0]);
				if (pair[1])
					free(pair[1]);
			}
		}
		else
			exit_code = 1;
		i++;
	}
	free(pair);
	return (exit_code);
}

/*	takes a token containing env variables, duplicates key & value
/	new variables are only handled in case of assigment ('=')
*/ 
void	ft_get_pair(char **pair, char *token, t_list *ev)
{
	if (!ft_strchr(token, '='))
	{
		if (ft_getenv(ev, token))
		{
			pair[0] = ft_strdup(token);
			pair[1] = ft_strdup(ft_getenv_v(ft_getenv(ev, token)));
		}
		else
		{
			pair[0] = NULL;
			pair[1] = NULL;
		}
	}
	else
		ft_env_split(pair, token);
}

void	ft_env_split(char **pair, char *s)
{
	int		i;

	i = 0;
	while (s[i] != '=')
		i++;
	pair[0] = ft_substr(s, 0, i);
	pair[1] = ft_substr(s, i + 1, ft_strlen(s) - i);
}