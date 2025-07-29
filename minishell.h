/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:25:49 by jkovacev          #+#    #+#             */
/*   Updated: 2025/07/29 17:34:26 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*---------------------------------------------------*/
/*---------------------INCLUDES----------------------*/
/*---------------------------------------------------*/

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "tokenizer/tokenizer.h"
# include "parsing/parsing.h"
# include "execution/execution.h"
# include "expansion/expansion.h"
# include "built-ins/built_ins.h"
# include "env_vars/env_vars.h"

/*---------------------------------------------------*/
/*----------------------DEFINES----------------------*/
/*---------------------------------------------------*/

# define PATH_MAX 4096
# define CYN   "\x1B[36m"
# define RESET "\x1B[0m"
# define BOLD "\033[1m"
# define UNBOLD "\033[0m"

/*---------------------------------------------------*/
/*--------------------GLOBAL-VAR---------------------*/
/*---------------------------------------------------*/

extern volatile sig_atomic_t	g_last_sig;

typedef struct s_ctx_holder
{
	t_token_context		*t_ctx;
	t_parse_ctx			*p_ctx;
	t_exec_ctx			*e_ctx;
}	t_ctx_holder;


/*	Enum?
 *	Exit code Conventions:
 *	0	- Success
 * 	1	- General Error
 * 	2	- Misuse of built-ins
 * 	126	- Invoked command failed to execute
 * 	127	- Command not found
 * 	128	- Invalid exit argument
 * 	130	- Termination by ctrl-c
 * 	255	- Exit status out of range/custom fatal error
 * 
 * 	129-255	- Exit via signal (128 + signum)
*/

#endif
