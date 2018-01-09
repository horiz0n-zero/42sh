/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_checkstatus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:43:44 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/14 15:24:28 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void	status_signaled(t_dispatch *const dispatch,
		t_cmd *const cmd)
{
	int				err;
	char			**argv;

	err = WTERMSIG(dispatch->foreground.status);
	if (err >= 23)
		err = SIGQUIT;
	ft_printf("\r\33[38;5;208m>> \33[38;5;196m%s\t\33[37m",
			dispatch->foreground.background.errors[err]);
	argv = cmd->argv;
	while (*argv)
		ft_printf("%s ", *argv++);
	write(STDOUT_FILENO, "\n", 1);
}

static inline void	status_stopped(t_dispatch *const dispatch, t_cmd *const cmd)
{
	t_back			*ptr;

	ptr = SUPER(dispatch)->foreground.background.get(dispatch, cmd->pid);
	if (ptr)
	{
		if (ptr->status & B_FOREGROUND)
			ptr->status = B_FOREGROUND | B_STOPPED;
		else
			ptr->status = B_BACKGROUND | B_STOPPED;
	}
	else
		SUPER(dispatch)->foreground.background.append(dispatch, cmd,
				B_FOREGROUND | B_STOPPED);
}

int					foreground_checkstatus(t_dispatch *const dispatch,
		t_cmd *const cmd)
{
	if (cmd->typeoff)
	{
		if (cmd->typeoff == TYPE_ANDAND
				&& WEXITSTATUS(dispatch->foreground.status))
			return (1);
		if (cmd->typeoff == TYPE_OROR
				&& !WEXITSTATUS(dispatch->foreground.status))
			return (1);
	}
	if (WIFSIGNALED(dispatch->foreground.status))
		status_signaled(dispatch, cmd);
	if (WIFSTOPPED(dispatch->foreground.status))
		status_stopped(dispatch, cmd);
	return (0);
}
