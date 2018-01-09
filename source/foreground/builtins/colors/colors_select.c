/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_select.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:13:50 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/12 16:13:53 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void				colors_show(t_dispatch *const dispatch,
		int *const color)
{
	ft_printf("%s%s", CAPS(UP).s, CAPS(UP).s);
	if (!color[3])
		ft_printf("\t%s[%3d]%s", CAPS(SO).s, *color, CAPS(SE).s);
	else
		ft_printf("\t[%3d]", *color);
	if (color[3] == 1)
		ft_printf("\t%s[%3d]%s", CAPS(SO).s, *(color + 1), CAPS(SE).s);
	else
		ft_printf("\t[%3d]", *(color + 1));
	if (color[3] == 2)
		ft_printf("\t%s[%3d]%s", CAPS(SO).s, *(color + 2), CAPS(SE).s);
	else
		ft_printf("\t[%3d]", *(color + 2));
	ft_printf("\t\33[38;2;%d;%d;%dmcolor\33[37m\n",
			*color, *(color + 1), *(color + 2));
	ft_printf("\t  -  \t  -  \t  -\n");
}

static void						change_direction(int *const color,
		const int isleft)
{
	if (isleft)
	{
		if (color[3] <= 0)
			color[3] = 2;
		else
			color[3] = color[3] - 1;
	}
	else
	{
		if (color[3] >= 2)
			color[3] = 0;
		else
			color[3] = color[3] + 1;
	}
}

static inline void				change_value(int *const color, const int plus)
{
	int							*ptr;

	if (!color[3])
		ptr = color;
	else if (color[3] == 1)
		ptr = color + 1;
	else
		ptr = color + 2;
	if (plus)
	{
		if (*ptr >= 255)
			*ptr = 0;
		else
			*ptr = *ptr + 1;
	}
	else
	{
		if (*ptr <= 0)
			*ptr = 255;
		else
			*ptr = *ptr - 1;
	}
}

static void						color_loop(t_dispatch *const dispatch,
		int *const color)
{
	static int64_t				data;
	static char *const			ptr = (void*)&data;
	ssize_t						size;

	while (42)
	{
		size = read(STDIN_FILENO, ptr, sizeof(int64_t));
		if (size == 1)
		{
			if (*ptr == 13 || *ptr == 10 || *ptr == 3)
				break ;
		}
		else if (size == 3)
		{
			if (ptr[2] == 'C')
				change_direction(color, false);
			else if (ptr[2] == 'D')
				change_direction(color, true);
			else if (ptr[2] == 'A')
				change_value(color, true);
			else if (ptr[2] == 'B')
				change_value(color, false);
		}
		colors_show(dispatch, color);
	}
}

void							*colors_select(t_dispatch *const dispatch)
{
	int							color[4];
	char						*choice;

	tcsetattr(STDIN_FILENO, TCSANOW, &dispatch->display.current);
	write(STDOUT_FILENO, CAPS(VI).s, CAPS(VI).l);
	color[0] = 255;
	color[1] = 255;
	color[2] = 255;
	color[3] = 1;
	ft_printf("\t  +  \t  +  \t  +\n\n\n");
	colors_show(dispatch, color);
	color_loop(dispatch, color);
	ft_vasprintf(&choice, "\33[38;2;%d;%d;%dm", color[0], color[1], color[2]);
	ft_printf("%s%s%s", CAPS(VE).s, CAPS(UP).s, CAPS(UP).s);
	tcsetattr(STDIN_FILENO, TCSANOW, &dispatch->display.saved);
	return (choice);
}
