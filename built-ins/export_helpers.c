/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:03:55 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/24 20:45:22 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../built-ins/built_ins.h"
#include "../execution/execution.h"
#include "../libft/libft.h"

// refactor handle_kv_pair here

static int count_exported(t_list *ev)
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

static t_env_var	**create_array_of_pointers(t_list *ev, int size)
{
	t_env_var	**array_of_vars;
	t_env_var	*env_var;
	int			i;

	array_of_vars = malloc(size * sizeof(t_env_var));
	if (!array_of_vars)
		return (NULL);
	i = 0;
	while (ev)
	{
		env_var = (t_env_var *)ev->content;
		if (env_var->value && env_var->exported)
		{
			array_of_vars[i] = env_var;	
		}
		i++;
		ev = ev->next;
	}
	return (array_of_vars);
}

static void	sort_vars(t_env_var **array_of_vars, int size)
{
	int			i;
	int			j;
	t_env_var	*temp;
	
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(array_of_vars[j]->key, array_of_vars[j + 1]->key) > 0)
			{
				temp = array_of_vars[j];
				array_of_vars[j] = array_of_vars[j + 1];
				array_of_vars[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
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
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(array_of_vars[i]->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(array_of_vars[i]->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);			
		}
		i++;
	}
	free(array_of_vars);
	return (true);
}
