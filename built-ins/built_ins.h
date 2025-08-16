/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:14:42 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/28 19:56:12 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

/*---------------------------------------------------*/
/*---------------------INCLUDES----------------------*/
/*---------------------------------------------------*/

# include "../minishell.h"
# include "../utils/utils.h"

/*---------------------------------------------------*/
/*----------------------STRUCTS----------------------*/
/*---------------------------------------------------*/

typedef enum e_sig_mode
{
	SIG_INTERACTIVE,
	SIG_NONINTERACTIVE,
	SIG_HEREDOC,
}	t_sig_mode;

/*---------------------------------------------------*/
/*---------------------FUNCTIONS---------------------*/
/*---------------------------------------------------*/

// cd
int			ft_cd(char **argv, t_list *lst);

// echo
int			ft_echo(char **tokens);

// env
int			ft_env(t_list *lst);
int			ft_modenv(t_list *lst, char *value);
t_list		*ft_getenv(t_list *lst, char *key);
char		*ft_getenv_v(t_list *lst);

// exit
int			ft_exit(t_exec_ctx *ctx, char *argv[]);
bool		ft_exit_sigeof(void);

// export
int			ft_export(char **tokens, t_list *ev, t_list *assignments);
t_env_var	**create_array_of_pointers(t_list *ev, int size);
void		sort_vars(t_env_var **array_of_vars, int size);
bool		export_no_args(t_list *ev);
bool		get_value(char **pair, t_assignment *a);

// pwd
int			ft_pwd(void);

// signals
void		ft_change_sigmode(t_sig_mode mode);
int			ft_get_last_sig_exit(int last_exit_code);

// unset
int			ft_unset(char **keys, t_list *lst, t_list *assignments);

#endif
