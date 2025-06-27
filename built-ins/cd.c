/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: culbrich <culbrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:55:18 by culbrich          #+#    #+#             */
/*   Updated: 2025/06/27 14:41:11 by culbrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

// changes cwd to path and updates env vars accordingly
int	ft_cd(char *path, t_list *lst)
{
	if (!path)
		path = ft_getenv_v(ft_getenv(lst, "HOME"));
	if (chdir(path))
		return (1);
	// will need protection against invalid input
	ft_modenv(ft_getenv(lst, "OLDPWD"), "PWD");
	ft_modenv(ft_getenv(lst, "PWD"), path);
	return (0);
}
