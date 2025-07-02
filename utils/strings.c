/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:22:23 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/02 19:05:17 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../libft/libft.h"

bool	is_str_equal(char *s1, char *s2)
{
	size_t	len1;

	len1 = ft_strlen(s1);
	if (len1 != ft_strlen(s2))
		return (false);
	return (ft_strncmp(s1, s2, len1) == 0);
}