/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:55:49 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/22 20:09:08 by jkovacev         ###   ########.fr       */
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
		return (0);
	return (1);
}

static bool	is_valid_key(char *token)
{
	int	i;

	i = 0;
	if (!ft_isalpha(token[i]) && token[i] != '_')
		return (false);
	i++;
	while (token[i] && token[i] != '=')
	{
		if (!ft_isalnum(token[i]) && token[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	ft_free_pair(char **pair)
{
	free(pair[0]);
	free(pair[1]);
}

static bool	handle_key_value_pair(t_list **ev, char **pair, char *token)
{
	if (ft_strchr(token, '='))
	{
		if (!ft_env_split(pair, token))
		{
			ft_free_pair(pair);
			return (false);
		}
	}
	else
	{
		pair[0] = ft_strdup(token);
		if (!pair[0])
			return (false);
	}
	if (!add_env_var(ev, pair[0], pair[1], true))
	{
		ft_free_pair(pair);	
		return (false);
	}
	return (true);
}

int	ft_export(char **argv, t_list *ev, t_list *assignments)
{
	int		i;
	char	*pair[2];
	
	(void)assignments; // remove after impl
	i = 1;
	if (!is_valid_key(argv[i]))
	{
		printf("bash: export: %s: not a valid identifier\n", argv[i]);
		return (1);
	}
	while (argv[i])
	{
		pair[0] = NULL;
		pair[1] = NULL;
		if (!handle_key_value_pair(&ev, pair, argv[i]))
			return (1);
		i++;		
	}
	return (0);
}
