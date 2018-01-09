/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_select.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 11:56:45 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/04 15:04:09 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void			select_pos(t_dispatch *const d, const int left)
{
	size_t			i;

	i = 0;
	while (i < d->display.select.count)
	{
		if (d->display.select.array[i].cursor)
		{
			d->display.select.array[i].cursor = false;
			break ;
		}
		i++;
	}
	if (left)
	{
		if (!i--)
			d->display.select.array[d->display.select.count - 1].cursor = true;
		else
			d->display.select.array[i].cursor = true;
		return ;
	}
	if (++i >= d->display.select.count)
		d->display.select.array->cursor = true;
	else
		d->display.select.array[i].cursor = true;
}

static void			select_this(t_dispatch *const dispatch)
{
	size_t			i;

	i = 0;
	while (i < dispatch->display.select.count)
	{
		if (dispatch->display.select.array[i].cursor)
		{
			if (dispatch->display.select.array[i].selected)
				dispatch->display.select.array[i].selected = false;
			else
				dispatch->display.select.array[i].selected = true;
		}
		i++;
	}
}

static void			select_loop(t_dispatch *const dispatch)
{
	int64_t			data;
	ssize_t			size;
	char *const		ptr = (void*)&data;

	while (1)
	{
		size = read(STDIN_FILENO, ptr, sizeof(int64_t));
		if (size == 1)
		{
			if (*ptr == 13)
				break ;
			if (*ptr == 32)
				select_this(dispatch);
			else if (*ptr == 9)
				select_pos(dispatch, false);
		}
		else if (size == 3)
		{
			if (*(ptr + 2) == 'C')
				select_pos(dispatch, false);
			else if (*(ptr + 2) == 'D')
				select_pos(dispatch, true);
			SUPER(dispatch)->display.select_print(dispatch);
		}
	}
}

void				display_select(t_dispatch *const dispatch)
{
	const size_t	index = dispatch->display.index;
	size_t			li;
	size_t			lili;

	if (!dispatch->display.select.count)
		return ;
	SUPER(dispatch)->display.end_line(dispatch);
	li = dispatch->display.select.count / dispatch->display.select.coz + 1;
	lili = li;
	while (lili--)
		write(STDOUT_FILENO, "\n", 1);
	lili = li;
	while (lili--)
		write(STDOUT_FILENO, CAPS(UP).s, CAPS(UP).l);
	ft_printf("%s%s", CAPS(SC).s, CAPS(VI).s);
	dispatch->display.select.array->cursor = true;
	dispatch->display.select.activated = true;
	SUPER(dispatch)->display.select_print(dispatch);
	select_loop(dispatch);
	ft_printf("%s%s%s", CAPS(VE).s, CAPS(RC).s, CAPS(CD).s);
	SUPER(dispatch)->display.goposition(index, dispatch);
	SUPER(dispatch)->display.selected(dispatch);
	dispatch->display.select.activated = false;
}
