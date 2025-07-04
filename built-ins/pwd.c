/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:55:56 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/02 21:18:38 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

// print current working directory
int	ft_pwd(t_list *lst)
{
	t_env_var	*env_var;

	env_var = (t_env_var *)ft_lstfind(lst, &get_env_value, "PWD");
	if (env_var->value)
		printf("%s\n", env_var->value);
	return (0);
}
