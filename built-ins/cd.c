/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:55:18 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/27 20:53:49 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include <sys/stat.h>

// changes cwd to path and updates env vars accordingly
int	ft_cd(char **argv, t_list *lst)
{
	if (array_size(argv) > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (!argv[1])
		argv[1] = ft_getenv_v(ft_getenv(lst, "HOME"));
	if (chdir(argv[1]))
	{
		printf("minishell: cd: %s: %s\n", argv[1], strerror(errno));
		return (1);
	}
	ft_modenv(ft_getenv(lst, "OLDPWD"), ft_getenv_v(ft_getenv(lst, "PWD")));
	ft_modenv(ft_getenv(lst, "PWD"), argv[1]);
	return (0);
}
