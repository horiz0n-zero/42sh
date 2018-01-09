/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tmp_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 11:08:14 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/02 14:42:34 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void					display_tmp_loop(t_dispatch *const dispatch)
{
	static int64_t		data;
	static char *const	ptr = (void*)&data;
	ssize_t				size;

	dispatch->display.work = WORKD_TXT;
	while (true)
	{
		size = read(STDIN_FILENO, ptr, sizeof(int64_t));
		if (size == 1)
		{
			SUPER(dispatch)->display.read_one(ptr, dispatch);
		}
		else
			SUPER(dispatch)->display.read_three(ptr, dispatch);
		if (!dispatch->display.work)
			return ;
	}
}
