/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:14:42 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/11 20:26:54 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

/*---------------------------------------------------*/
/*---------------------INCLUDES----------------------*/
/*---------------------------------------------------*/

# include "../minishell.h"

/*---------------------------------------------------*/
/*---------------------FUNCTIONS---------------------*/
/*---------------------------------------------------*/

// cd
int	    ft_cd(char *path, t_list *lst);

// echo
int	    ft_echo(char **tokens);
int	    ft_echo_option(char *s);

// env
int	    ft_env(t_list *lst);
int	    ft_modenv(t_list *lst, char *value);
t_list	*ft_getenv(t_list *lst, char *key);
char	*ft_getenv_v(t_list *lst);
char	*ft_getenv_k(t_list *lst);

// exit
int		ft_exit(t_execution_context *ctx, char *argv[]);

// export
int		ft_export(char **tokens, t_list *ev, t_list *assignments);
void    ft_get_pair(char **pair, char *token, t_list *ev);
void    ft_env_split(char **pair, char *s);

// pwd
int	    ft_pwd(void);

// signals
void	ft_sig_interactive(int sig);
void	ft_sig_noninteractive(int sig);
void	ft_change_sigmode(bool interactive);

// unset
int	    ft_unset(char **keys, t_list *lst, t_list *assignments);
void	ft_lstdelfill(t_list **start, t_list *to_del);

#endif
