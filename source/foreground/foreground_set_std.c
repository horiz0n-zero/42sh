/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_set_std.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstoian <kstoian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 10:03:50 by jeblonde          #+#    #+#             */
/*   Updated: 2018/01/03 18:05:21 by kstoian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void	set_stdrat(t_red *const red)
{
	if ((red->flag & R_CLOSED) && ((red->x == 1) ||
		(red->x == -1 && red->in == STDIN_FILENO)))
	{
		red->x = STDOUT_FILENO;
		red->in = red->x;
	}
	else if ((red->flag & R_CLOSED) && ((red->x == 2)))
		red->in = red->x;
	dup2(red->y, red->x);
}

static inline void	ar_red_exec(t_red *const red)
{
	int				fd;

	if (red->flag & R_CLOSED)
	{
		fd = open("/dev/null", O_RDWR);
		red->y = fd;
		red->out = fd;
		set_stdrat(red);
	}
	else
	{
		if (red->x == -1)
			red->x = red->in;
		if (red->y == -1)
			red->y = red->out;
		dup2(red->y, red->x);
	}
}

static inline void	foreground_ar(t_cmd *const cmd)
{
	t_red			*ptr;

	ptr = cmd->red;
	while (ptr)
	{
		if (ptr->flag & R_ISRAT)
			ar_red_exec(ptr);
		ptr = ptr->next;
	}
}

void				foreground_set_std(t_task *const task, t_cmd *const cmd)
{
	if (task->red)
		foreground_set_std_task(task);
	if (task->stdin != STDIN_FILENO && cmd->stdin == STDIN_FILENO)
		cmd->stdin = task->stdin;
	if (task->stdout != STDOUT_FILENO && cmd->stdout == STDOUT_FILENO)
		cmd->stdout = task->stdout;
	if (task->stderr != STDERR_FILENO && cmd->stderr == STDERR_FILENO)
		cmd->stderr = task->stderr;
	if (cmd->stdin != STDIN_FILENO)
	{
		close(STDIN_FILENO);
		dup2(cmd->stdin, STDIN_FILENO);
	}
	if (cmd->stdout != STDOUT_FILENO)
	{
		close(STDOUT_FILENO);
		dup2(cmd->stdout, STDOUT_FILENO);
	}
	if (cmd->stderr != STDERR_FILENO)
	{
		close(STDERR_FILENO);
		dup2(cmd->stderr, STDERR_FILENO);
	}
	if (cmd->red)
		foreground_ar(cmd);
}
