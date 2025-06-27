/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: culbrich <culbrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:55:56 by culbrich          #+#    #+#             */
/*   Updated: 2025/06/27 14:44:32 by culbrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

// print current working directory
int	ft_pwd(t_list *lst)
{
	t_list		*env_ptr;
	t_env_var	*env_var;

	env_ptr = ft_getenv(lst, "PWD");
	env_var = (t_env_var *)env_ptr->content;
	if (env_var->value)
		printf("%s\n", env_var->value);
	return (0);
}
