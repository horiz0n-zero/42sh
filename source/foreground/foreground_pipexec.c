/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_pipexec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstoian <kstoian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:07:31 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 17:02:51 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void				proc_execute(t_dispatch *const dispatch,
		t_task *const task, t_cmd *const cmd)
{
	extern char			**environ;

	SUPER(dispatch)->foreground.set_std(task, cmd);
	SUPER(dispatch)->foreground.setsignal(DEFAULT);
	signal(SIGTSTP, SIG_IGN);
	setpgid(0, dispatch->foreground.background.self_group);
	if (!cmd->type)
	{
		execve(*cmd->argv, cmd->argv, environ);
		ft_printf(FATAL_EXECVE, *cmd->argv, cmd);
		exit(0);
	}
	else if (cmd->type & 1)
	{
		exec_red(dispatch, NULL, cmd);
		exit(0);
	}
	exit(((t_builtfunc)cmd->func)(dispatch, cmd->argv));
}

static void				foreground_proc(t_dispatch *const dispatch,
		t_task *const task, t_cmd *cmd, int *const fd)
{
	extern char			**environ;

	SUPER(dispatch)->foreground.set_red(dispatch, cmd);
	close(fd[0]);
	if (cmd->stdout != STDOUT_FILENO)
		close(cmd->stdout);
	cmd->stdout = fd[1];
	if (fd[2] != STDIN_FILENO)
	{
		if (cmd->stdin != STDIN_FILENO)
			close(cmd->stdin);
		cmd->stdin = fd[2];
	}
	proc_execute(dispatch, task, cmd);
}

static inline void		lastchild(int *const fd, t_dispatch *const dispatch,
		t_task *const task, t_cmd *const cmd)
{
	SUPER(dispatch)->foreground.set_red(dispatch, cmd);
	if (cmd->stdin != STDIN_FILENO)
		close(cmd->stdin);
	cmd->stdin = fd[2];
	proc_execute(dispatch, task, cmd);
}

void					*foreground_pipexec(t_dispatch *const dispatch,
		t_task *const task, t_cmd *cmd)
{
	pid_t			pid;
	int				fd[3];
	extern char		**environ;

	fd[2] = STDIN_FILENO;
	while (cmd && cmd->next && cmd->typeoff == TYPE_OR)
	{
		pipe(fd);
		if (!(pid = fork()))
			foreground_proc(dispatch, task, cmd, fd);
		else
			SUPER(dispatch)->foreground.background.append_pid(dispatch, pid);
		close(fd[1]);
		if (fd[2] != STDIN_FILENO)
			close(fd[2]);
		fd[2] = fd[0];
		cmd = cmd->next;
	}
	if (!(pid = fork()))
		lastchild(fd, dispatch, task, cmd);
	close(fd[2]);
	SUPER(dispatch)->foreground.background.append_pid(dispatch, pid);
	SUPER(dispatch)->foreground.background.wait_pids(dispatch);
	return (cmd);
}
