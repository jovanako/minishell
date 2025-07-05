/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:23:17 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/05 11:36:11 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdbool.h>
#include "../expansion/expansion.h"

bool	is_str_equal(char *s1, char *s2);
void	delete_token(void *t);
char	*ft_strcpy(char *s);
#endif