/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 21:20:50 by jkovacev          #+#    #+#             */
/*   Updated: 2025/08/23 21:25:01 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <sys/stat.h>

bool	is_dir(char *path)
{
	struct stat path_stat;

	if (stat(path, &path_stat) != 0)
		return (false);
	return (S_ISDIR(path_stat.st_mode));
}