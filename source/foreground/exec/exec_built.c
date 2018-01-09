/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 13:09:32 by jeblonde          #+#    #+#             */
/*   Updated: 2017/12/12 17:40:49 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				exec_built(t_dispatch *const dispatch, t_task *const task,
		t_cmd *const cmd)
{
	int				fd[3];

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDIN_FILENO);
	fd[2] = dup(STDERR_FILENO);
	if (cmd->red)
		SUPER(dispatch)->foreground.set_red(dispatch, cmd);
	SUPER(dispatch)->foreground.set_std(task, cmd);
	dispatch->foreground.status = ((t_builtfunc)cmd->func)(dispatch, cmd->argv);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[2], STDERR_FILENO);
}
