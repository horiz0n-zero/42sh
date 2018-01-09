/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_taskpipexec.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 15:47:59 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/23 10:56:41 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const t_execute		g_exec_functions[] =
{
	[CMD_OK] = exec_pure,
	[CMD_RED] = exec_red,
	[CMD_BUILT] = exec_built
};

static inline void			foreground_task_setstd(t_task *const task,
		int *const fd)
{
	close(fd[0]);
	if (task->stdout != STDOUT_FILENO)
		close(task->stdout);
	task->stdout = fd[1];
	if (fd[2] != STDIN_FILENO)
	{
		if (task->stdin != STDIN_FILENO)
			close(task->stdin);
		task->stdin = fd[2];
	}
}

static void					foreground_taskpipe_execute(
		t_dispatch *const dispatch, t_task *const task, int *const fd)
{
	t_cmd					*cmd;

	foreground_task_setstd(task, fd);
	cmd = task->cmd;
	while (cmd)
	{
		if (cmd->typeoff == TYPE_OR)
		{
			cmd = SUPER(dispatch)->foreground.pipexec(dispatch, task, cmd);
			continue ;
		}
		if (cmd->type == CMD_BUILT)
			SUPER(dispatch)->foreground.set_std(task, cmd);
		g_exec_functions[cmd->type](dispatch, task, cmd);
		if (cmd->typeoff == TYPE_ANDAND &&
				WEXITSTATUS(dispatch->foreground.status))
			break ;
		if (cmd->typeoff == TYPE_OROR &&
				!WEXITSTATUS(dispatch->foreground.status))
			break ;
		cmd = cmd->next;
	}
	exit(0);
}

static void					foreground_taskpipe_execlast(
		t_dispatch *const dispatch, t_task *const task)
{
	t_cmd					*cmd;

	cmd = task->cmd;
	while (cmd)
	{
		if (cmd->typeoff == TYPE_OR)
		{
			cmd = SUPER(dispatch)->foreground.pipexec(dispatch, task, cmd);
			continue ;
		}
		g_exec_functions[cmd->type](dispatch, task, cmd);
		if (cmd->typeoff == TYPE_ANDAND &&
				WEXITSTATUS(dispatch->foreground.status))
			break ;
		if (cmd->typeoff == TYPE_OROR &&
				!WEXITSTATUS(dispatch->foreground.status))
			break ;
		cmd = cmd->next;
	}
	exit(0);
}

void						*foreground_taskpipexec(t_dispatch *const dispatch,
		t_task *task)
{
	pid_t					pid;
	int						fd[3];

	if (!task || !task->next)
		return (task);
	fd[2] = STDIN_FILENO;
	while (task && task->next && task->type & TASKI_OR)
	{
		pipe(fd);
		if (!(pid = fork()))
			foreground_taskpipe_execute(dispatch, task, fd);
		close(fd[1]);
		fd[2] = fd[0];
		task = task->next;
	}
	if (!(pid = fork()))
	{
		if (task->stdin != STDIN_FILENO)
			close(task->stdin);
		task->stdin = fd[2];
		foreground_taskpipe_execlast(dispatch, task);
	}
	else
		waitpid(pid, &dispatch->foreground.status, dispatch->foreground.wait);
	return (task->next);
}
