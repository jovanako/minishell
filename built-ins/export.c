/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:55:49 by culbrich          #+#    #+#             */
/*   Updated: 2025/08/22 20:41:28 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include "../err_printf/err_printf.h"
#include "../utils/utils.h"

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

static bool	is_valid_key(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (false);
	i++;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
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

static bool	handle_kv_pair(t_list **ev, t_list *asgn, char **pair, char *arg)
{
	t_assignment	*a;

	if (ft_strchr(arg, '='))
	{
		if (!ft_env_split(pair, arg))
		{
			ft_free_pair(pair);
			return (false);
		}
	}
	else
	{
		pair[0] = ft_strdup(arg);
		if (!pair[0])
			return (false);
	}
	a = ft_lstfind(asgn, &match_assignment_key, pair[0]);
	if (!pair[1] && a)
		return (get_value(pair, a));
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

	if (array_size(argv) == 1)
	{
		if (!export_no_args(ev))
			return (false);
		return (true);
	}
	i = 1;
	if (!is_valid_key(argv[i]))
	{
		err_printf("minishell: export: %s: not a valid identifier\n",
			argv[i]);
		return (1);
	}
	while (argv[i])
	{
		pair[0] = NULL;
		pair[1] = NULL;
		if (!handle_kv_pair(&ev, assignments, pair, argv[i]))
			return (1);
		i++;
	}
	return (0);
}
