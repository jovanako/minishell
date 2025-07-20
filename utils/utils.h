/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:23:17 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/19 10:33:21 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdbool.h>
#include "../expansion/expansion.h"
#include "../parsing/parsing.h"

bool	is_str_equal(char *s1, char *s2);
void	delete_token(void *t);
bool 	match_assignment_key(void *a, void *k);
char	*ft_strcpy(char *s);
void	ft_free_strarray(char **s_a);
bool	ft_isnumber(char *s);

#endif
