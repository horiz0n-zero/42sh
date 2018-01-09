/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstoian <kstoian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:34:37 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/05 15:10:55 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void					display_got_capacities(t_dispatch *const dispatch,
		...)
{
	va_list					args;
	char					*cap;
	int						index;

	index = 0;
	va_start(args, dispatch);
	while ((cap = va_arg(args, char*)))
	{
		if (tgetflag(cap) || !(dispatch->display.caps[index].s =
					tgetstr(cap, NULL)))
			SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
		dispatch->display.caps[index].l =
			ft_strlen(dispatch->display.caps[index].s);
		index++;
	}
	va_end(args);
}

static void					display_set_termios(t_dispatch *const dispatch)
{
	struct winsize			win;

	ft_memset((char*)&dispatch->display.current, sizeof(struct termios));
	dispatch->display.current.c_iflag |= (IGNPAR | IXOFF | IXON);
	dispatch->display.current.c_oflag |= (ONLCR | OPOST);
	dispatch->display.current.c_lflag |= ISIG;
	dispatch->display.current.c_cc[VMIN] = 1;
	dispatch->display.current.c_cc[VTIME] = 0;
	if (tcgetattr(STDIN_FILENO, &dispatch->display.saved) == -1)
		SUPER(dispatch)->exit(dispatch, "No struct termios available.");
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &dispatch->display.current) == -1)
		SUPER(dispatch)->exit(dispatch, "Can't set the termios struct.");
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &win) == -1)
		SUPER(dispatch)->exit(dispatch, "Can't get the screen size.");
	dispatch->display.co = (size_t)win.ws_col;
	dispatch->display.li = (size_t)win.ws_row;
	dispatch->display.work = WORKD_MAIN;
}

static void					display_init_color(t_dispatch *const dispatch)
{
	int						fd;

	dispatch->display.properties.location_color = COPY("\33[38;5;21m");
	dispatch->display.properties.separator_string = COPY("<<");
	dispatch->display.properties.separator_color = COPY("\33[38;5;163m");
	dispatch->display.properties.prompt_string = COPY(">");
	dispatch->display.properties.prompt_color = COPY("\33[38;5;161m");
	dispatch->display.properties.text_color = COPY("\33[37m");
	dispatch->display.properties.builtins_color = COPY("\33[38;05;226m");
	if (dispatch->base)
	{
		fd = open(ft_stcjoin(dispatch->base, "_colors"),
				O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
		dispatch->display.colors = fd;
		SUPER(dispatch)->display.readcolor(dispatch);
	}
}

void						ctor_display(t_dispatch *const dispatch)
{
	uname(&dispatch->display.node);
	if (tgetent(NULL, SUPER(dispatch)->env.get(dispatch, "TERM")) == -1)
		exit(EXIT_FAILURE);
	display_got_capacities(dispatch, "cr", "le", "nd", "up", "do",
				"bl", "rc", "sc", "cl", "cd", "ce", "dc", "vi", "ve",
				"ti", "te", "al", "cm", "vb", "ho", "ch", "us", "ue",
				"so", "se", NULL);
	display_set_termios(dispatch);
	dispatch->display.index = 0;
	dispatch->display.len = 0;
	dispatch->display.buffer_size = 2;
	dispatch->display.select.activated = false;
	dispatch->display.select.app = false;
	dispatch->display.stop = false;
	ft_printf("%s%s", CAPS(TI).s, CAPS(CL).s);
	dispatch->display.buffer = malloc(sizeof(char) *
			(dispatch->display.buffer_size + 1));
	if (!dispatch->display.buffer)
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size + 1);
	dispatch->display.selection = false;
	dispatch->display.pasteboard = NULL;
	display_init_color(dispatch);
	SUPER(dispatch)->display.prompt(NULL, 0, dispatch);
}
