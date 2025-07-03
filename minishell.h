/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:25:49 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/03 09:50:56 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include "tokenizer/tokenizer.h"
#include "parsing/parsing.h"
#include "execution/execution.h"
#include "expansion/expansion.h"

t_list	*copy_env_vars(char *envp[]);
#endif