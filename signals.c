/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apashkov <apashkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:22:55 by apashkov          #+#    #+#             */
/*   Updated: 2024/04/03 15:26:39 by apashkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigint = 0;

static void	signal_processing1(int sig)
{
	if (sig == SIGINT)
	{
		g_sigint = SIGINT;
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	signal_processing2(int sig)
{
	if (sig == SIGINT)
		g_sigint = SIGINT;
}

static void	signal_processing3(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		g_sigint = SIGINT;
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	signals(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, &signal_processing1);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2)
	{
		signal(SIGINT, &signal_processing2);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == 3)
	{
		signal(SIGINT, &signal_processing3);
		signal(SIGQUIT, SIG_IGN);
	}
}
