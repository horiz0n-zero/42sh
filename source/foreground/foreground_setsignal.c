/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_setsignal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:36:36 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/13 15:42:17 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void	sig_self(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGSEGV, signal_exit);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGABRT, signal_exit);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGWINCH, signal_window);
	signal(SIGCHLD, signal_child);
}

static inline void	sig_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGSEGV, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGWINCH, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
}

static inline void	sig_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGSEGV, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
}

void				foreground_setsignal(const int type)
{
	if (type == DEFAULT)
		sig_default();
	else if (type == SELF)
		sig_self();
	else
		sig_ignore();
}
