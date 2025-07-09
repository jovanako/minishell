/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: culbrich <culbrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:56:02 by culbrich          #+#    #+#             */
/*   Updated: 2025/06/27 14:18:57 by culbrich         ###   ########.fr       */
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
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// in noninteractive mode SIGINT and SIGQUIT both print a newline
void	ft_sig_noninteractive(int sig)
{
	// TODO kill child process (via global var?)
	g_last_sig = sig;
	rl_on_new_line();
}

// changes the function that handles incoming SIGINT and SIGQUIT signals
void	ft_change_sigmode(int interactive)
{
	struct sigaction	action;

	if (interactive)
		action.sa_handler = &ft_sig_interactive;
	else
		action.sa_handler = &ft_sig_noninteractive;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

