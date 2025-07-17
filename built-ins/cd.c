/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:55:18 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/17 20:36:01 by jkovacev         ###   ########.fr       */
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
	ft_modenv(ft_getenv(lst, "OLDPWD"), ft_getenv_v(ft_getenv(lst, "PWD")));
	ft_modenv(ft_getenv(lst, "PWD"), path);
	return (0);
}
