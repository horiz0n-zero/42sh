/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_right_left.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 13:39:53 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/02 11:58:41 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		display_right(t_dispatch *const dispatch)
{
	if (dispatch->display.index < dispatch->display.len)
	{
		if (ISREDGE(dispatch))
			write(STDOUT_FILENO, CAPS(DO).s, CAPS(DO).l);
		else
			write(STDOUT_FILENO, CAPS(ND).s, CAPS(ND).l);
		dispatch->display.index++;
	}
	else
		write(STDOUT_FILENO, CAPS(BL).s, CAPS(BL).l);
}

void		display_left(t_dispatch *const dispatch)
{
	size_t	co;

	if (dispatch->display.index)
	{
		if (ISLEDGE(dispatch))
		{
			co = dispatch->display.co;
			write(STDOUT_FILENO, CAPS(UP).s, CAPS(UP).l);
			while (co--)
				write(STDOUT_FILENO, CAPS(ND).s, CAPS(ND).l);
		}
		else
			write(STDOUT_FILENO, CAPS(LE).s, CAPS(LE).l);
		dispatch->display.index--;
	}
	else
		write(STDOUT_FILENO, CAPS(BL).s, CAPS(BL).l);
}

void		display_word_right(t_dispatch *const dispatch)
{
	while (dispatch->display.buffer[dispatch->display.index] &&
	dispatch->display.buffer[dispatch->display.index] != ' ')
		SUPER(dispatch)->display.right(dispatch);
	while (dispatch->display.buffer[dispatch->display.index] &&
	dispatch->display.buffer[dispatch->display.index] == ' ')
		SUPER(dispatch)->display.right(dispatch);
}

void		display_word_left(t_dispatch *const dispatch)
{
	while (dispatch->display.index > 0 &&
			dispatch->display.buffer[dispatch->display.index] != ' ')
		SUPER(dispatch)->display.left(dispatch);
	while (dispatch->display.index > 0 &&
			dispatch->display.buffer[dispatch->display.index] == ' ')
		SUPER(dispatch)->display.left(dispatch);
}
