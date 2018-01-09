/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_keyboard_up_down.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:43:45 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 11:46:03 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				display_up(t_dispatch *const dispatch)
{
	t_history_node	*ptr;

	if (dispatch->history.index)
		dispatch->history.index--;
	if (!dispatch->history.count)
		return ((void)write(STDOUT_FILENO, CAPS(BL).s, CAPS(BL).l));
	ptr = dispatch->history.array + dispatch->history.index;
	SUPER(dispatch)->display.goposition(0, dispatch);
	while ((size_t)ptr->len + 1 > dispatch->display.buffer_size)
		SUPER(dispatch)->display.expand(dispatch);
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size);
	SUPER(dispatch)->memory.move(dispatch->display.buffer, ptr->src,
			(size_t)ptr->len);
	dispatch->display.len = ptr->len;
	ft_printf("%s%s", CAPS(CD).s, dispatch->display.buffer);
	SUPER(dispatch)->display.goposition(ptr->index, dispatch);
}

void				display_down(t_dispatch *const dispatch)
{
	t_history_node	*ptr;

	dispatch->history.index++;
	if (dispatch->history.index >= dispatch->history.count)
	{
		if (dispatch->history.count)
			dispatch->history.index = dispatch->history.count - 1;
	}
	if (!dispatch->history.count)
		return ((void)write(STDOUT_FILENO, CAPS(BL).s, CAPS(BL).l));
	ptr = dispatch->history.array + dispatch->history.index;
	SUPER(dispatch)->display.goposition(0, dispatch);
	while ((size_t)ptr->len + 1 > dispatch->display.buffer_size)
		SUPER(dispatch)->display.expand(dispatch);
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size);
	SUPER(dispatch)->memory.move(dispatch->display.buffer, ptr->src,
			(size_t)ptr->len);
	dispatch->display.len = (size_t)ptr->len;
	write(STDOUT_FILENO, CAPS(CD).s, CAPS(CD).l);
	write(STDOUT_FILENO, dispatch->display.buffer, dispatch->display.len);
	SUPER(dispatch)->display.goposition(ptr->index, dispatch);
}

void				display_line_up(t_dispatch *const dispatch)
{
	int				delta;

	delta = (int)dispatch->display.index - (int)dispatch->display.co;
	if (delta >= 0)
	{
		delta = (int)dispatch->display.co;
		while (delta--)
			SUPER(dispatch)->display.left(dispatch);
	}
}

void				display_line_down(t_dispatch *const dispatch)
{
	int				delta;

	delta = (int)dispatch->display.index + (int)dispatch->display.co;
	if (delta <= (int)dispatch->display.len)
	{
		delta = (int)dispatch->display.co;
		while (delta--)
			SUPER(dispatch)->display.right(dispatch);
	}
}
