/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:22:23 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/24 19:49:10 by jkovacev         ###   ########.fr       */
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

char	*ft_strcpy(char *s)
{
	char	*result;
	int		i;
	
	i = 0;
	result = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

void	ft_free_strarray(char **s_a)
{
	int i;

	i = 0;
	if (s_a)
	{
		while (s_a[i])
			free(s_a[i++]);
		free(s_a);
	}
}

bool	ft_isnumber(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i++]))
			return (false);
	}
	return (true);
}

int	array_size(char **arr)
{
	int	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}
