/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_start_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 14:35:02 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/02 10:27:14 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		display_start_line(t_dispatch *const dispatch)
{
	size_t	line;
	size_t	res;

	if (dispatch->display.index)
	{
		res = dispatch->display.index + dispatch->display.indes;
		if (res >= dispatch->display.co)
		{
			line = res / dispatch->display.co;
			while (line--)
				write(STDOUT_FILENO, dispatch->display.caps[UP].s,
						dispatch->display.caps[UP].l);
			if ((res = dispatch->display.indes + dispatch->display.index %
						dispatch->display.co))
				ft_printf("\33[%zdD", res);
			ft_printf("\33[%zdC", dispatch->display.indes);
		}
		else
			ft_printf("\33[%zdD", dispatch->display.index);
		dispatch->display.index = 0;
	}
}
