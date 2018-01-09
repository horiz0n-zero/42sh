/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_bg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:34:24 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/05 15:14:55 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void			place_bg(t_dispatch *const dispatch, t_back *const back)
{
	if (!(back->status & B_FOREGROUND))
	{
		ft_printf("%sAlready in background : %s\33[37m\n",
				dispatch->display.properties.location_color, back->argv[0]);
		return ;
	}
	back->status = B_BACKGROUND | B_RUN;
	kill(SIGCONT, back->pid);
}

static void			*get_last(t_dispatch *const dispatch)
{
	t_back			*ptr;

	ptr = dispatch->foreground.background.back;
	while (ptr && ptr->next)
		ptr = ptr->next;
	return (ptr);
}

static void			bg_argv(t_dispatch *const dispatch, char **argv,
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
				place_bg(dispatch, ptr);
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

int					built_bg(t_dispatch *const dispatch, char **argv)
{
	t_back			*back;

	if (*++argv)
		bg_argv(dispatch, argv, NULL);
	else
	{
		back = get_last(dispatch);
		if (!back)
		{
			ft_printf("bg: no current job.\n");
			return (0);
		}
		place_bg(dispatch, back);
	}
	return (0);
}
