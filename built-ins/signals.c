/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:56:02 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/10 15:53:01 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

// TODO SIGQUIT still prints "^\", should do nothing
// TODO EOF (ctrl-d) needs to print/call exit

// in interactive mode SIGINT resets the prompt, SIGQUIT is ignored
void	ft_sig_interactive(int sig)
{
	g_last_sig = sig;
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// in noninteractive mode SIGINT and SIGQUIT both print a newline
void	ft_sig_noninteractive(int sig)
{
	g_last_sig = sig;
	rl_on_new_line();
}

// changes the function that handles incoming SIGINT and SIGQUIT signals
void	ft_change_sigmode(bool interactive)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	if (interactive)
		action.sa_handler = &ft_sig_interactive;
	else
		action.sa_handler = &ft_sig_noninteractive;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	rl_catch_signals = interactive;
}

