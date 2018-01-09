/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_end_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 14:42:10 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/07 14:47:58 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		display_end_line(t_dispatch *const dispatch)
{
	size_t	line;
	size_t	super;

	if (dispatch->display.index < dispatch->display.len)
	{
		SUPER(dispatch)->display.start_line(dispatch);
		dispatch->display.index = dispatch->display.len;
		ft_printf("\33[%zdD", dispatch->display.indes);
		if (dispatch->display.len + dispatch->display.indes >=
				dispatch->display.co)
		{
			line = (dispatch->display.indes + dispatch->display.len) /
				dispatch->display.co;
			super = line;
			while (line--)
				write(STDOUT_FILENO, dispatch->display.caps[DO].s,
						dispatch->display.caps[DO].l);
		}
		else
			super = dispatch->display.len + dispatch->display.indes;
		if (super)
			ft_printf("\33[%zdC", super);
	}
}
