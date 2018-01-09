/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_goposition.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 10:57:02 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/02 14:38:37 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static int			ftintput(int c)
{
	write(1, &c, 1);
	return (0);
}

static inline void	display_goto(t_dispatch *const dispatch, size_t li,
		size_t co)
{
	tputs(tgoto(CAPS(CH).s, 0, (int)co), STDOUT_FILENO, ftintput);
	if (li > 0)
		while (li--)
			write(STDOUT_FILENO, CAPS(UP).s, CAPS(UP).l);
}

void				display_goposition(const size_t pos,
		t_dispatch *const dispatch)
{
	size_t			total_buffer;
	size_t			total_cursor;
	size_t			end_line;
	size_t			cur_line;

	total_buffer = dispatch->display.indes + dispatch->display.len;
	total_cursor = dispatch->display.indes + pos;
	end_line = total_buffer / dispatch->display.co;
	cur_line = total_cursor / dispatch->display.co;
	if (ISLEDGE(dispatch))
	{
		write(STDOUT_FILENO, "\r\n", 2);
		write(STDOUT_FILENO, CAPS(LE).s, CAPS(LE).l);
	}
	display_goto(dispatch, end_line - cur_line, total_cursor %
			dispatch->display.co);
	dispatch->display.index = pos;
}
