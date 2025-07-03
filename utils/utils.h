/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:23:17 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/03 08:43:44 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdbool.h>
#include "../expansion/expansion.h"

bool	is_str_equal(char *s1, char *s2);
bool	get_env_value(void *content, void *var_key);
void	delete_env_var(void *var);
void	delete_token(void *t);
#endif