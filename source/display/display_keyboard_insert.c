/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_keyboard_insert.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 14:19:20 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/02 14:21:15 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		display_append(const char c, t_dispatch *const dispatch)
{
	size_t	index;

	if (++dispatch->display.len > dispatch->display.buffer_size)
		SUPER(dispatch)->display.expand(dispatch);
	if (dispatch->display.buffer[dispatch->display.index])
	{
		SUPER(dispatch)->string.apush(dispatch->display.buffer,
				(int)dispatch->display.index, c);
		ft_printf("%s%s", CAPS(CD).s, dispatch->display.buffer +
				dispatch->display.index++);
		index = dispatch->display.index;
		dispatch->display.index = dispatch->display.len;
		SUPER(dispatch)->display.goposition(index, dispatch);
	}
	else
	{
		write(STDOUT_FILENO, &c, 1);
		if (ISREDGE(dispatch))
			write(STDOUT_FILENO, CAPS(DO).s, CAPS(DO).l);
		dispatch->display.buffer[dispatch->display.index++] = c;
	}
}
