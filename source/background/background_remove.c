/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_remove.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 11:52:33 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/16 16:21:07 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void		back_done(t_dispatch *const dispatch, t_back *const back)
{
	int			i;

	i = 0;
	if (back->status & B_BACKGROUND)
		ft_printf("%s>> %-5d > %s%s\t\33[38;2;0;255;42mdone\n\33[37m",
				dispatch->display.properties.prompt_color, back->pid,
				dispatch->display.properties.location_color, *back->argv);
	while (back->argv[i])
		free(back->argv[i++]);
	free(back->argv);
	free(back);
}

void			background_remove(t_dispatch *const dispatch, const pid_t pid)
{
	t_back		*ptr;
	t_back		*last;

	last = NULL;
	ptr = dispatch->foreground.background.back;
	while (ptr)
	{
		if (ptr->pid == pid)
		{
			if (!last)
				dispatch->foreground.background.back = ptr->next;
			else
				last->next = ptr->next;
			return (back_done(dispatch, ptr));
		}
	}
}
