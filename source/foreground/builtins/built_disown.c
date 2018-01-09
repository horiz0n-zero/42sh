/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_disown.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 15:01:18 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 17:42:02 by afeuerst         ###   ########.fr       */
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

static void			disown_argv(t_dispatch *const dispatch, char **argv)
{
	char			**pargv;
	int				i;
	t_back			*ptr;

	i = 0;
	pargv = SUPER(dispatch)->foreground.background.percent(dispatch, argv);
	while (pargv[i])
	{
		if (*pargv[i] >= '0' && *pargv[i] <= '9')
		{
			ptr = SUPER(dispatch)->foreground.background.get(dispatch,
					SUPER(dispatch)->string.atoi(pargv[i]));
			if (ptr)
				SUPER(dispatch)->foreground.background.remove(dispatch,
						ptr->pid);
			else
				ft_printf("%sNo such process %s.\33[37m\n",
						dispatch->display.properties.location_color, argv[i]);
		}
		else
			ft_printf("%sNo such process %s.\33[37m\n",
						dispatch->display.properties.location_color, argv[i]);
		free(pargv[i++]);
	}
}

int					built_disown(t_dispatch *const dispatch, char **argv)
{
	t_back			*ptr;

	if (*++argv)
		disown_argv(dispatch, argv);
	else
	{
		ptr = fg_last_back(dispatch);
		if (ptr)
			SUPER(dispatch)->foreground.background.remove(dispatch, ptr->pid);
		else
			ft_printf("disown: no current job\n");
	}
	return (0);
}
