/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:59:47 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/05 11:36:26 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VARS_H
# define ENV_VARS_H

#include "../libft/libft.h"
#include "../utils/utils.h"

typedef struct s_env_var
{
	char	*key;
	char	*value;
	bool	exported;
}	t_env_var;

bool		is_valid_env_var_char(char c);
void		delete_env_var(void *var);
bool		add_env_var(t_list *env_vars, char *key, char *val, bool exported);
t_env_var	*get_env_var(t_list *env_vars, char *key);
t_list		*create_env_vars(char *envp[]);
#endif