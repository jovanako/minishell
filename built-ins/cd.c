/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: culbrich <culbrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:55:18 by culbrich          #+#    #+#             */
/*   Updated: 2025/08/20 14:52:14 by culbrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include <sys/stat.h>

//	returns 0 on success, 1 on error
static int	ft_update_pwd(t_list *lst)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = ft_strcpy(ft_getenv_v(ft_getenv(lst, "PWD")));
	if (!oldpwd)
		return (1);
	ft_modenv(ft_getenv(lst, "OLDPWD"), oldpwd);
	pwd = NULL;
	pwd = getcwd(pwd, PATH_MAX);
	if (!pwd)
		return (1);
	ft_modenv(ft_getenv(lst, "PWD"), pwd);
	return (0);
}

//	changes cwd to path and updates env vars accordingly
//	returns 0 on success, 1 on error
int	ft_cd(char **argv, t_list *lst)
{
	if (array_size(argv) > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (!argv[1])
		argv[1] = ft_getenv_v(ft_getenv(lst, "HOME"));
	if (chdir(argv[1]))
	{
		printf("minishell: cd: %s: %s\n", argv[1], strerror(errno));
		return (1);
	}
	if (ft_update_pwd(lst))
		return (1);
	return (0);
}
