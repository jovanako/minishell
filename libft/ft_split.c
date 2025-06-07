/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:29:01 by jkovacev          #+#    #+#             */
/*   Updated: 2024/11/28 17:13:27 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int		i;
	int		count;
	char	prev;

	i = 0;
	count = 0;
	prev = c;
	while (s[i])
	{
		if (s[i] != c && prev == c)
			count++;
		prev = s[i++];
	}
	return (count);
}

static char	*extract_word(char const *s, char c,
				char **result, int res_position)
{
	char	*start;
	char	*end;

	start = (char *)s;
	while (*start && *start == c)
	{
		start++;
	}
	end = ft_strchr(start, c);
	if (end == NULL)
		end = start + ft_strlen(start);
	result[res_position] = ft_substr(s, start - s, end - start);
	return (end);
}

static void	free_result(char **result)
{
	int		i;

	i = 0;
	while (result[i])
		free(result[i++]);
	free(result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;
	int		i;
	char	*current;

	word_count = count_words(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (0);
	result[word_count] = (void *)0;
	i = 0;
	current = (char *)s;
	while (i < word_count)
	{
		current = extract_word(current, c, result, i);
		if (result[i] == NULL)
		{
			free_result(result);
			return (NULL);
		}
		i++;
	}
	return (result);
}
