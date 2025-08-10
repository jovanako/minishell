/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_list_to_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:26:00 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/28 19:26:25 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	**free_and_return(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i])
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
	return (NULL); 
}

char	**ev_list_to_arr(t_list *env_vars)
{
	int			i;
	char		**result;
	t_env_var	*var;
	char		*str_var1;
	char		*str_var2;

	i = 0;
	result = malloc((ft_lstsize(env_vars) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (env_vars)
	{
		var = (t_env_var *)env_vars->content;
		str_var1 = ft_strjoin(var->key, "=");
		if (!str_var1)
			return (free_and_return(result));
		str_var2 = ft_strjoin(str_var1, var->value);
		free(str_var1);
		if (!str_var2)
			return (free_and_return(result));
		result[i++] = str_var2;
		env_vars = env_vars->next;
	}
	result[i] = NULL;
	return (result);
}
