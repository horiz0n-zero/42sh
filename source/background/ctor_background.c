/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 11:54:06 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/14 11:31:21 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const char	*g_errors[] =
{
	[SIGHUP] = "terminal line hangup",
	[SIGINT] = "interrupt program",
	[SIGQUIT] = "quit program",
	[SIGILL] = "illegal instruction",
	[SIGTRAP] = "trace trap",
	[SIGABRT] = "abort program",
	[SIGEMT] = "emulate instruction executed",
	[SIGFPE] = "floating-point exception",
	[SIGKILL] = "kill program",
	[SIGBUS] = "bus error",
	[SIGSEGV] = "segmentation violation",
	[SIGSYS] = "non-existent system call invoked",
	[SIGPIPE] = "write on a pipe with no reader",
	[SIGALRM] = "real-time timer expired",
	[SIGTERM] = "software termination signal",
	[SIGURG] = "urgent condition present on socket",
	[SIGSTOP] = "stop (cannot be caught or ignored)",
	[SIGTSTP] = "stop",
	[SIGCONT] = "continue after stop",
	[SIGTTIN] = "background read attempted from control terminal",
	[SIGTTOU] = "background write attempted to control terminal"
};

static inline void	background_init_pids(t_dispatch *const dispatch)
{
	dispatch->foreground.background.pids_size = 2;
	dispatch->foreground.background.pids = malloc(sizeof(pid_t) * 2);
	if (!dispatch->foreground.background.pids)
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	dispatch->foreground.background.pids_count = 0;
}

void				ctor_background(t_dispatch *const dispatch)
{
	pid_t	group;

	group = getpgrp();
	while (tcgetpgrp(STDIN_FILENO) != (group = getpgrp()))
		kill(group, SIGTTIN);
	setpgid(group, group);
	tcsetpgrp(STDIN_FILENO, group);
	dispatch->foreground.background.self_group = group;
	dispatch->foreground.background.pipe = -1;
	dispatch->foreground.background.back = NULL;
	background_init_pids(dispatch);
	dispatch->foreground.background.errors = (const char**)g_errors;
	dispatch->foreground.background.turn = 0;
}
