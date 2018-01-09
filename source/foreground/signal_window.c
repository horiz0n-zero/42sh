/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 10:05:31 by jeblonde          #+#    #+#             */
/*   Updated: 2018/01/02 15:27:12 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void		reprint_current_line(t_dispatch *const dispatch)
{
	const size_t		index = dispatch->display.index;

	write(STDOUT_FILENO, CAPS(CL).s, CAPS(CL).l);
	SUPER(dispatch)->display.prompt(NULL, 0, dispatch);
	dispatch->display.index = dispatch->display.len;
	write(STDOUT_FILENO, dispatch->display.buffer, dispatch->display.len);
	SUPER(dispatch)->display.goposition(index, dispatch);
}

void					signal_window(int signal)
{
	t_dispatch *const	dispatch = get_dispatch(NULL);
	struct winsize		win;
	size_t				coz;

	(void)signal;
	coz = 0;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &win);
	dispatch->display.co = win.ws_col;
	dispatch->display.li = win.ws_row;
	if (dispatch->display.select.activated)
	{
		if (dispatch->display.co < dispatch->display.select.len)
			return ;
		coz = dispatch->display.co / dispatch->display.select.len;
		dispatch->display.select.coz = coz;
		SUPER(dispatch)->display.select_print(dispatch);
	}
	reprint_current_line(dispatch);
}
