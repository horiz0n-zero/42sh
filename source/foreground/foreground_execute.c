/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 10:37:00 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/03 15:21:58 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const t_execute	g_exec_functions[] =
{
	[CMD_OK] = exec_pure,
	[CMD_RED] = exec_red,
	[CMD_BUILT] = exec_built
};

static void				execute_task(t_dispatch *const dispatch,
		t_task *const task)
{
	t_cmd				*cmd;

	cmd = task->cmd;
	while (cmd)
	{
		if (cmd->typeoff == TYPE_OR && cmd->next)
		{
			cmd = SUPER(dispatch)->foreground.pipexec(dispatch, task, cmd);
			if (SUPER(dispatch)->foreground.checkstatus(dispatch, cmd))
				break ;
			cmd = cmd->next;
			continue ;
		}
		g_exec_functions[cmd->type](dispatch, task, cmd);
		if (SUPER(dispatch)->foreground.checkstatus(dispatch, cmd))
			break ;
		cmd = cmd->next;
	}
}

static void				exec_sub(t_dispatch *const dispatch, t_task *const task)
{
	pid_t				pid;

	pid = fork();
	if (!pid)
	{
		setpgid(0, 0);
		execute_task(dispatch, task);
		exit(dispatch->foreground.status);
	}
	else if (pid == -1)
		ft_printf(FATAL_FORK, "in subshell execution.");
	else
		waitpid(pid, &dispatch->foreground.status, dispatch->foreground.wait);
}

void					foreground_execute(t_dispatch *const dispatch)
{
	t_task				*task;

	task = dispatch->foreground.collection.task;
	if (dispatch->display.stop)
		return ;
	while (task)
	{
		if (task->type & TASKI_OR)
		{
			task = SUPER(dispatch)->foreground.taskpipexec(dispatch, task);
			continue ;
		}
		if (task->type & TASK_SUBSHELL)
			exec_sub(dispatch, task);
		else
			execute_task(dispatch, task);
		task = task->next;
	}
	tcsetpgrp(STDIN_FILENO, dispatch->foreground.background.self_group);
}
