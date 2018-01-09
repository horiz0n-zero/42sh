/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 15:57:49 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 15:33:20 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void				child_signaled(t_dispatch *const dispatch,
		t_back *const back, int signal)
{
	const int			isstoped = WIFSTOPPED(signal);
	const int			exit_status = WTERMSIG(signal);

	if (isstoped)
	{
		if (back->status & B_FOREGROUND)
			back->status = B_FOREGROUND | B_STOPPED;
		else
			back->status = B_BACKGROUND | B_STOPPED;
		return ;
	}
	ft_printf("\r%s> %d <>> %s%s\t%s\n\33[37m",
		dispatch->display.properties.prompt_color, back->pid,
		dispatch->display.properties.builtins_color,
		dispatch->foreground.background.errors[exit_status], *back->argv);
	SUPER(dispatch)->foreground.background.remove(dispatch, back->pid);
}

void					signal_child(int signal)
{
	pid_t				pid;
	static t_dispatch	*dispatch = NULL;
	t_back				*back;

	if (!dispatch)
		dispatch = get_dispatch(NULL);
	if ((pid = waitpid(-1, &signal, WNOHANG)) > 0)
	{
		back = SUPER(dispatch)->foreground.background.get(dispatch, pid);
		if (back)
		{
			if (WIFEXITED(signal))
				SUPER(dispatch)->foreground.background.remove(dispatch, pid);
			else if (WIFSIGNALED(signal))
				child_signaled(dispatch, back, signal);
		}
	}
}
