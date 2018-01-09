/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:30:14 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 13:03:59 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void		history_insert(t_dispatch *const dispatch)
{
	const size_t		i = dispatch->history.count++;
	int					index;

	index = 0;
	while (BUFFER(index))
	{
		if (BUFFER(index) == '\n')
			BUFFER(index) = ' ';
		index++;
	}
	dispatch->history.array[i].src = dispatch->display.buffer;
	dispatch->history.array[i].len = (uint64_t)dispatch->display.len;
	dispatch->history.array[i].index = (uint32_t)dispatch->display.index;
}

void					history_write(t_dispatch *const dispatch)
{
	if (dispatch->history.count + 1 >= dispatch->history.size)
		SUPER(dispatch)->history.expand(dispatch);
	history_insert(dispatch);
}
