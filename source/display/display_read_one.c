/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_read_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:34:54 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/03 15:27:56 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void	special_case(const char *const ptr,
		t_dispatch *const dispatch)
{
	if (*ptr == '\f')
		SUPER(dispatch)->display.lclear(dispatch);
	else if (*ptr == 9)
		SUPER(dispatch)->display.selection(dispatch);
	else if (!dispatch->display.work && *ptr == 3)
		SUPER(dispatch)->display.cancel(dispatch);
	else if (dispatch->display.work && *ptr == 3)
	{
		dispatch->display.work = 0;
		dispatch->display.stop = true;
	}
	else if (*ptr == 28 || (*ptr == 4 && !dispatch->display.len))
		SUPER(dispatch)->dtor(dispatch);
	else if (*ptr == 1)
		SUPER(dispatch)->display.home(dispatch);
	else if (*ptr == 5)
		SUPER(dispatch)->display.end(dispatch);
	else if (*ptr == 11)
		SUPER(dispatch)->display.copy(dispatch);
	else if (*ptr == 16)
		SUPER(dispatch)->display.paste(dispatch);
	else if (*ptr == 18)
		SUPER(dispatch)->history.search(dispatch);
}

void				display_read_one(const char *ptr,
		t_dispatch *const dispatch)
{
	size_t			index;

	if (*ptr == 127)
		SUPER(dispatch)->display.remove(dispatch);
	else if (*ptr >= '!' || *ptr == 32)
		SUPER(dispatch)->display.append(*ptr, dispatch);
	else
	{
		if (*ptr == 13)
		{
			index = dispatch->display.index;
			SUPER(dispatch)->display.end(dispatch);
			dispatch->display.index = index;
			if (!dispatch->display.work)
				SUPER(dispatch)->start(dispatch);
			else
			{
				SUPER(dispatch)->display.append('\n', dispatch);
				dispatch->display.work = WORKD_MAIN;
			}
		}
		else
			special_case(ptr, dispatch);
	}
}
