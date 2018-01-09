/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_keyboard_cut_paste.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 09:37:13 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/27 10:52:33 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void				copy_print(t_dispatch *const dispatch, const int s,
		const int index)
{
	int					i;

	i = 0;
	if (index < s)
	{
		while (i < index)
			write(STDOUT_FILENO, dispatch->display.buffer + i++, 1);
		write(STDOUT_FILENO, CAPS(US).s, CAPS(US).l);
		while (i < s)
			write(STDOUT_FILENO, dispatch->display.buffer + i++, 1);
		write(STDOUT_FILENO, CAPS(UE).s, CAPS(UE).l);
		while (i < (int)dispatch->display.len)
			write(STDOUT_FILENO, dispatch->display.buffer + i++, 1);
	}
	else
	{
		while (i < s)
			write(STDOUT_FILENO, dispatch->display.buffer + i++, 1);
		write(STDOUT_FILENO, CAPS(US).s, CAPS(UE).l);
		while (i < index)
			write(STDOUT_FILENO, dispatch->display.buffer + i++, 1);
		write(STDOUT_FILENO, CAPS(UE).s, CAPS(UE).l);
		while (i < (int)dispatch->display.len)
			write(STDOUT_FILENO, dispatch->display.buffer + i++, 1);
	}
}

static void				copy_loop(t_dispatch *const dispatch, const int start,
		int index)
{
	static int64_t		data;
	static char *const	ptr = (void*)&data;
	ssize_t				size;

	while (42)
	{
		size = read(STDIN_FILENO, ptr, sizeof(int64_t));
		if (size == 1)
		{
			if (*ptr == 3 || *ptr == 28 || *ptr == 4 || *ptr == 13 ||
					*ptr == 11)
				break ;
		}
		else if (size == 3)
		{
			if (*(ptr + 2) == 'C')
				SUPER(dispatch)->display.right(dispatch);
			else if (*(ptr + 2) == 'D')
				SUPER(dispatch)->display.left(dispatch);
			index = (int)dispatch->display.index;
			SUPER(dispatch)->display.start_line(dispatch);
			copy_print(dispatch, start, index);
			SUPER(dispatch)->display.goposition((size_t)index, dispatch);
		}
	}
}

static void				*get_copy(t_dispatch *const dispatch, const int s,
		const int c)
{
	char				*new;

	if (s < c)
	{
		if (!(new = malloc((size_t)(c - s) + 1)))
			malloc_exit();
		memory_move(new, dispatch->display.buffer + s, (size_t)(c - s));
		*(new + (c - s)) = 0;
	}
	else
	{
		if (!(new = malloc((size_t)(s - c) + 1)))
			malloc_exit();
		memory_move(new, dispatch->display.buffer + c, (size_t)(s - c));
		*(new + (s - c)) = 0;
	}
	return (new);
}

void					display_copy(t_dispatch *const dispatch)
{
	const int			index = (int)dispatch->display.index;

	if (dispatch->display.pasteboard)
	{
		free(dispatch->display.pasteboard);
		dispatch->display.pasteboard = NULL;
	}
	copy_loop(dispatch, index, 0);
	dispatch->display.pasteboard = get_copy(dispatch, index,
			(int)dispatch->display.index);
	SUPER(dispatch)->display.start_line(dispatch);
	ft_printf("%s%s", CAPS(CD).s, dispatch->display.buffer);
	SUPER(dispatch)->display.goposition((size_t)index, dispatch);
}

void					display_paste(t_dispatch *const dispatch)
{
	const int			index = (int)dispatch->display.index;
	size_t				len;

	if (!dispatch->display.pasteboard)
		return ((void)write(STDOUT_FILENO, CAPS(BL).s, CAPS(BL).l));
	len = ft_strlen(dispatch->display.pasteboard);
	while (dispatch->display.len + len + 1 > dispatch->display.buffer_size)
		SUPER(dispatch)->display.expand(dispatch);
	string_astrpush(dispatch->display.pasteboard, dispatch->display.buffer,
			(int)dispatch->display.index);
	dispatch->display.len += len;
	SUPER(dispatch)->display.start_line(dispatch);
	ft_printf("%s%s", CAPS(CD).s, dispatch->display.buffer);
	SUPER(dispatch)->display.goposition((size_t)index + len, dispatch);
}
