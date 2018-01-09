/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_task.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 11:18:24 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/12 15:52:11 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const t_task		g_task =
{
	TASK_COMMON,
	STDIN_FILENO,
	STDOUT_FILENO,
	STDERR_FILENO,
	0,
	0,
	NULL,
	NULL,
	NULL,
	NULL
};

void					*new_task(void)
{
	t_task				*task;

	if (!(task = malloc(sizeof(t_task))))
		malloc_exit();
	*task = g_task;
	return (task);
}
