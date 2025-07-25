/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:56:02 by culbrich          #+#    #+#             */
/*   Updated: 2025/07/21 15:06:43 by jkovacev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

// TODO SIGQUIT still prints "^\", should do nothing
// TODO EOF (ctrl-d) needs to print/call exit

// in interactive mode SIGINT resets the prompt, SIGQUIT is ignored
static void	ft_sig_interactive(int sig)
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
static void	ft_sig_noninteractive(int sig)
{
	g_last_sig = sig;
	rl_on_new_line();
}

int	ft_sig_heredoc(void)
{
	if (g_last_sig == SIGINT)
		rl_done = 1;
	return (0);
}

// changes the function that handles incoming SIGINT and SIGQUIT signals
void	ft_change_sigmode(t_sig_mode mode)
{
	struct sigaction	action;

	g_last_sig = 0;
	ft_bzero(&action, sizeof(action));
	if (mode == SIG_INTERACTIVE)
		action.sa_handler = &ft_sig_interactive;
	else if (mode == SIG_NONINTERACTIVE)
		action.sa_handler = &ft_sig_noninteractive;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

