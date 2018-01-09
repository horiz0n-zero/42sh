/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 12:42:31 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/22 15:43:26 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		display_remove(t_dispatch *const dispatch)
{
	if (dispatch->display.len && dispatch->display.index)
	{
		dispatch->display.len--;
		if (dispatch->display.buffer[--dispatch->display.index])
			SUPER(dispatch)->string.kpush(dispatch->display.buffer,
					(int)dispatch->display.index);
		else
			dispatch->display.buffer[dispatch->display.index] = 0;
		if (ISREDGE(dispatch))
			ft_printf("%s\033[%dC", dispatch->display.caps[UP].s,
					dispatch->display.co);
		else
			ft_printf("%s", dispatch->display.caps[LE].s);
		ft_printf("%s%s", dispatch->display.caps[CD].s,
				dispatch->display.buffer + dispatch->display.index);
		SUPER(dispatch)->display.goposition(dispatch->display.index, dispatch);
	}
}
