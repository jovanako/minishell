/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: culbrich <culbrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:14:42 by culbrich          #+#    #+#             */
/*   Updated: 2025/06/27 14:42:03 by culbrich         ###   ########.fr       */
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
int	    ft_modenv(t_list *lst, char *key);
t_list	*ft_getenv(t_list *lst, char *key);
char	*ft_getenv_v(t_list *lst);
char	*ft_getenv_k(t_list *lst);

// exit
void	ft_exit(t_list **lst, int exit_code);

// export

// pwd
int	    ft_pwd(t_list *lst);

// signals
void	ft_sig_interactive(int sig);
void	ft_sig_noninteractive(int sig);
void	ft_change_sigmode(int interactive);

// unset
int	    ft_unset(char **keys, t_list *lst);
void	ft_lstdelfill(t_list **start, t_list *to_del);

#endif