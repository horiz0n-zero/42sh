/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_fg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 15:00:06 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/05 15:15:22 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void			*fg_last_back(t_dispatch *const dispatch)
{
	t_back			*ptr;

	ptr = dispatch->foreground.background.back;
	if (ptr)
	{
		while (ptr->next)
			ptr = ptr->next;
		return (ptr);
	}
	return (NULL);
}

static void			place_fg(t_dispatch *const dispatch, t_back *const ptr)
{
	tcsetpgrp(STDIN_FILENO, ptr->pid);
	kill(ptr->pid, SIGCONT);
	if (ptr->status & B_FOREGROUND)
		ptr->status = B_FOREGROUND | B_RUN;
	else
		ptr->status = B_BACKGROUND | B_RUN;
	waitpid(ptr->pid, &dispatch->foreground.status, dispatch->foreground.wait);
	if (WIFSTOPPED(dispatch->foreground.status))
	{
		if (ptr->status & B_FOREGROUND)
			ptr->status = B_FOREGROUND | B_STOPPED;
		else
			ptr->status = B_BACKGROUND | B_STOPPED;
	}
}

static void			fg_argv(t_dispatch *const dispatch, char **argv,
		char **pargv)
{
	int				i;
	t_back			*ptr;

	i = 0;
	if (!(pargv = SUPER(dispatch)->foreground.background.percent(dispatch,
					argv)))
		return ;
	while (pargv[i])
	{
		if (*pargv[i] >= '0' && *pargv[i] <= '9')
		{
			ptr = SUPER(dispatch)->foreground.background.get(dispatch,
					SUPER(dispatch)->string.atoi(pargv[i]));
			if (ptr)
				place_fg(dispatch, ptr);
			else
				ft_printf("%sNo such process %s.\33[37m\n",
						dispatch->display.properties.location_color, argv[i]);
		}
		else
			ft_printf("%sNo such process %s.\33[37m\n",
						dispatch->display.properties.location_color, argv[i]);
		free(pargv[i++]);
	}
	free(pargv);
}

int					built_fg(t_dispatch *const dispatch, char **argv)
{
	t_back			*ptr;

	if (*++argv)
		fg_argv(dispatch, argv, NULL);
	else
	{
		ptr = fg_last_back(dispatch);
		if (ptr)
			place_fg(dispatch, ptr);
		else
			ft_printf("fg: no current job\n");
	}
	return (0);
}
