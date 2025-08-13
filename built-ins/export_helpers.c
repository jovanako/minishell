/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:03:55 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/28 19:56:05 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include "../libft/libft.h"

// refactor handle_kv_pair here

t_env_var	**create_array_of_pointers(t_list *ev, int size)
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
			array_of_vars[i] = env_var;
		i++;
		ev = ev->next;
	}
	return (array_of_vars);
}

void	sort_vars(t_env_var **array_of_vars, int size)
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

bool	get_value(char **pair, t_assignment *a)
{
	pair[1] = ft_strdup(a->value);
	if (!pair[1])
	{
		free(pair[0]);
		return (false);
	}
	return (true);
}
