/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:41:01 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/28 19:46:53 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

static int	count_exported(t_list *ev)
{
	t_env_var	*var;
	int			count;

	count = 0;
	while (ev)
	{
		var = (t_env_var *)ev->content;
		if (var->exported)
			count++;
		ev = ev->next;
	}
	return (count);
}

static void	print_sorted(t_env_var **array_of_vars, int *i)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(array_of_vars[*i]->key, STDOUT_FILENO);
	ft_putstr_fd("=", STDOUT_FILENO);
	ft_putstr_fd("\"", STDOUT_FILENO);
	ft_putstr_fd(array_of_vars[*i]->value, STDOUT_FILENO);
	ft_putstr_fd("\"", STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

bool	export_no_args(t_list *ev)
{
	t_env_var	**array_of_vars;
	int			size;
	int			i;

	size = count_exported(ev);
	array_of_vars = create_array_of_pointers(ev, size);
	if (!array_of_vars)
		return (false);
	sort_vars(array_of_vars, size);
	i = 0;
	while (i < size - 1)
	{
		if (array_of_vars[i]->value && array_of_vars[i]->exported)
			print_sorted(array_of_vars, &i);
		i++;
	}
	free(array_of_vars);
	return (true);
}
