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
#include "../execution/execution.h"

// TODO SIGQUIT still prints "^\", should do nothing

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
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)", STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
}

static void	ft_sig_heredoc(int sig)
{
	g_last_sig = sig;
	rl_on_new_line();
}

// changes the function that handles incoming SIGINT and SIGQUIT signals
void	ft_change_sigmode(t_sig_mode mode)
{
	struct sigaction	action_sigint;
	struct sigaction	action_sigquit;

	rl_event_hook = 0;
	ft_bzero(&action_sigint, sizeof(action_sigint));
	ft_bzero(&action_sigquit, sizeof(action_sigquit));
	if (mode == SIG_INTERACTIVE)
	{
		action_sigint.sa_handler = &ft_sig_interactive;
		action_sigquit.sa_handler = SIG_IGN;
	}
	else if (mode == SIG_NONINTERACTIVE)
	{
		action_sigint.sa_handler = &ft_sig_noninteractive;
		action_sigquit.sa_handler = &ft_sig_noninteractive;
	}
	else if (mode == SIG_HEREDOC)
	{
		action_sigint.sa_handler = &ft_sig_heredoc;
		action_sigquit.sa_handler = SIG_IGN;
		rl_event_hook = heredoc_event_hook;
	}
	sigaction(SIGINT, &action_sigint, NULL);
	sigaction(SIGQUIT, &action_sigquit, NULL);
}

int	ft_get_last_sig_exit(int last_exit_code)
{
	int	new_exit_code;

	if (g_last_sig != 0)
		new_exit_code = g_last_sig + 128;
	else
		new_exit_code = last_exit_code;
	g_last_sig = 0;
	return (new_exit_code);
}
