/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:00:02 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/03 21:43:09 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../built-ins/built_ins.h"

char	*ft_cmdpath(t_list *lst, char *cmd)
{
    int		i;
    char	*path;
    char	*full_cmd;
    char	*cmd_path;
    char	**path_array;

	full_cmd = ft_strjoin("/", cmd);
	path = ft_getenv_v(ft_getenv(lst, "PATH"));
	path_array = ft_split(path, ':');
	i = 0;
	while (path_array[i])
	{
		if (!(cmd_path = ft_strjoin(path_array[i], full_cmd)))
			return (NULL);
		if (access(cmd_path, F_OK) == 0)
		{
			ft_free_strarray(path_array);
			free(full_cmd);
			return (cmd_path);
		}
		i++;
	}
	ft_free_strarray(path_array);
	free(full_cmd);
	return (NULL);
}
