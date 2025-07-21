/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:55:49 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/21 15:22:12 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static int	ft_env_split(char **pair, char *s)
{
	int		i;

	i = 0;
	while (s[i] != '=')
		i++;
	pair[0] = ft_substr(s, 0, i);
	pair[1] = ft_substr(s, i + 1, ft_strlen(s) - i);
	if (!pair[0] || !pair[1])
		return (1);
	return (0);
}

/*	takes a token containing env variables, duplicates key & value
/	new variables are only handled in case of assigment ('=')
*/ 
static void	ft_get_pair(char **pair, char *token, t_list *ev)
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

static void	ft_free_pair(char **pair)
{
	if (pair[0])
		free(pair[0]);
	if (pair[1])
		free(pair[1]);
}

/*	adds one or more given env vals to global scope
/	creates a new env val if needed
/	returns 0 if all tokens were exported, 1 if at least one failed
*/
int	ft_export(char **tokens, t_list *ev, t_list *assignments)
{
	int		i;
	int		exit_code;
	char	*pair[2];

	(void)assignments; // remove after impl
	i = 1;
	exit_code = 0;
	while (tokens[i])
	{
		ft_get_pair(pair, tokens[i], ev);
		if (pair[0])
		{
			if (!add_env_var(&ev, pair[0], pair[1], 1))
			{
				exit_code = 1;
				ft_free_pair(pair);
			}
		}
		else
			exit_code = 1;
		i++;
	}
	return (exit_code);
}
