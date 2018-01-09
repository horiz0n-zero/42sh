/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_set_red.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:34:34 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 14:55:41 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void	set_stds(t_cmd *const cmd, t_red *const red,
		const int fd)
{
	if (red->x == 0 || (red->x == -1 && red->in == STDIN_FILENO))
	{
		if (cmd->stdin != STDIN_FILENO)
			close(cmd->stdin);
		cmd->stdin = fd;
	}
	else if (red->x == 1 || (red->x == -1 && red->in == STDOUT_FILENO))
	{
		if (cmd->stdout != STDOUT_FILENO)
			close(cmd->stdout);
		cmd->stdout = fd;
	}
	else
	{
		if (cmd->stderr != STDERR_FILENO)
			close(cmd->stderr);
		cmd->stderr = fd;
	}
}

void				foreground_set_red(t_dispatch *const dispatch,
		t_cmd *const cmd)
{
	t_red			*ptr;
	int				fd;

	ptr = cmd->red;
	while (ptr)
	{
		if (ptr->flag & R_ISRAT)
		{
			ptr = ptr->next;
			continue ;
		}
		if ((fd = open(ptr->file, ptr->mode, dispatch->foreground.red_mode))
				< 0)
		{
			ptr = ptr->next;
			continue ;
		}
		set_stds(cmd, ptr, fd);
		ptr = ptr->next;
	}
}
