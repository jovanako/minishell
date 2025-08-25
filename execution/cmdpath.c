/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:00:02 by culbrich          #+#    #+#             */
/*   Updated: 2025/08/25 20:21:49 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../built-ins/built_ins.h"

static char	*ft_cmdpath_free(char **path_array, char *full_cmd, char *ret)
{
	ft_free_strarray(path_array);
	if (full_cmd)
		free(full_cmd);
	return (ret);
}

char	*ft_cmdpath(t_list *lst, char *cmd)
{
	int		i;
	char	*path;
	char	*full_cmd;
	char	*cmd_path;
	char	**path_array;

	full_cmd = ft_strjoin("/", cmd);
	if (!full_cmd)
		return (NULL);
	path = ft_getenv_v(ft_getenv(lst, "PATH"));
	path_array = ft_split(path, ':');
	if (!path_array)
		return (ft_cmdpath_free(path_array, full_cmd, NULL));
	i = 0;
	while (path_array[i])
	{
		cmd_path = ft_strjoin(path_array[i], full_cmd);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK) == 0)
			return (ft_cmdpath_free(path_array, full_cmd, cmd_path));
		free(cmd_path);
		i++;
	}
	return (ft_cmdpath_free(path_array, full_cmd, NULL));
}
