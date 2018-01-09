/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 13:19:53 by jeblonde          #+#    #+#             */
/*   Updated: 2017/12/17 14:50:31 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void	pure_parent(t_dispatch *const dispatch, t_cmd *const cmd)
{
	if (cmd->typeoff == TYPE_AND)
	{
		SUPER(dispatch)->foreground.background.append(dispatch, cmd,
				B_RUN | B_BACKGROUND);
		dispatch->foreground.background.turn = 1;
		ft_printf("%s>> %d %s> %s\t\33[38;2;0;255;42mlaunched\n\33[37m",
				dispatch->display.properties.prompt_color, cmd->pid,
				dispatch->display.properties.location_color, *cmd->argv);
	}
	else
	{
		tcsetpgrp(STDIN_FILENO, cmd->pid);
		signal(SIGCHLD, SIG_DFL);
		waitpid(cmd->pid, &dispatch->foreground.status,
				dispatch->foreground.wait);
		signal(SIGCHLD, signal_child);
		tcsetpgrp(STDIN_FILENO, dispatch->foreground.background.self_group);
	}
}

void				exec_pure(t_dispatch *const dispatch, t_task *const task,
		t_cmd *const cmd)
{
	extern char		**environ;

	if (!(cmd->pid = fork()))
	{
		if (cmd->red)
			SUPER(dispatch)->foreground.set_red(dispatch, cmd);
		cmd->pid = getpid();
		setpgid(cmd->pid, cmd->pid);
		if (cmd->typeoff != TYPE_AND)
			tcsetpgrp(STDIN_FILENO, cmd->pid);
		SUPER(dispatch)->foreground.set_std(task, cmd);
		SUPER(dispatch)->foreground.setsignal(DEFAULT);
		execve(*cmd->argv, cmd->argv, environ);
		ft_printf(FATAL_EXECVE, cmd->argv ? *cmd->argv : "BAD", cmd);
		exit(1);
	}
	else if (cmd->pid == -1)
		ft_printf(FATAL_FORK, *cmd->argv);
	else
		pure_parent(dispatch, cmd);
}
