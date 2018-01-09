/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_set_std_task.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 17:03:37 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 17:13:20 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void	set_norminette(t_task *const task, t_red *const red,
		const int fd)
{
	if (red->x == 2)
	{
		if ((red->flag & R_CLOSED) || red->x == 2)
			close(task->stderr);
		dup2(fd, red->x);
		task->stderr = fd;
	}
}

static inline void	set_stdrat(t_task *const task, t_red *const red,
		const int fd)
{
	if (red->x == 0)
	{
		if ((red->flag & R_CLOSED) && (red->x == 0 || red->in != STDIN_FILENO ||
			(red->x == -1 && red->in == STDIN_FILENO)))
			close(task->stdin);
		if (red->x == -1)
			dup2(fd, red->in);
		else
			dup2(fd, red->x);
		task->stdout = fd;
	}
	else if (red->x == 1 || (red->x == -1 && red->in == STDOUT_FILENO))
	{
		if ((red->flag & R_CLOSED) && (red->x == 1 ||
			red->in != STDOUT_FILENO ||
			(red->x == -1 && red->in == STDOUT_FILENO)))
			close(task->stdout);
		if (red->x == -1)
			dup2(fd, red->in);
		else
			dup2(fd, red->x);
		task->stdout = fd;
	}
	else
		set_norminette(task, red, fd);
}

static inline void	ar_red_exec(t_task *const task, t_red *const red)
{
	int				fd;

	if (red->flag & R_CLOSED)
	{
		fd = open("/dev/null", O_RDWR);
		set_stdrat(task, red, fd);
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

static inline void	foreground_ar(t_task *const task)
{
	t_red			*ptr;

	ptr = task->red;
	while (ptr)
	{
		if (ptr->flag & R_ISRAT)
			ar_red_exec(task, ptr);
		ptr = ptr->next;
	}
}

void				foreground_set_std_task(t_task *const task)
{
	foreground_ar(task);
}
