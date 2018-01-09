/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_here_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 11:12:05 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/23 09:42:23 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const t_readfunc		g_reads[] =
{
	display_read_one,
	display_read_one,
	display_read_one,
	display_read_three,
	display_read_more,
	display_read_more,
	display_read_more,
	display_read_more
};

void						display_here_loop(t_dispatch *const dispatch,
		int *const stop)
{
	static int64_t			data;
	static char *const		ptr = (void*)&data;
	ssize_t					size;

	dispatch->display.work = WORKD_TXT;
	while (true)
	{
		if ((size = read(STDIN_FILENO, ptr, sizeof(int64_t))) == 1)
		{
			if (*ptr == 13)
			{
				SUPER(dispatch)->display.append('\n', dispatch);
				dispatch->display.work = WORKD_MAIN;
				return ;
			}
			if (*ptr == 3 || *ptr == 28 || *ptr == 4)
			{
				*stop = true;
				write(STDOUT_FILENO, "\n", 1);
				dispatch->display.work = WORKD_MAIN;
				return ;
			}
		}
		g_reads[size](ptr, dispatch);
	}
}
