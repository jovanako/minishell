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

// TODO main loop needs to check for EOF input -> cleanly exits shell

// in interactive mode SIGINT resets the prompt, SIQUIT is ignored
void	ft_sig_interactive(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = 130;
		printf("\n");
		// weird functions, needs testing
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// in noninteractive mod SIGINT and SIGQUIT both print a newline
void	ft_sig_noninteractive(int sig)
{
	(void)sig;
	rl_on_new_line();
}

// changes the function that handles incoming SIGINT and SIGQUIT signals
void	ft_change_sigmode(int interactive)
{
	struct sigaction	action;

	// might need init
	if (interactive)
		action.sa_handler = &ft_sig_interactive;
	else
		action.sa_handler = &ft_sig_noninteractive;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

