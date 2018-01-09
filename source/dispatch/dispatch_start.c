/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:34:13 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/05 14:21:07 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void	dispatch_display_routine(t_dispatch *const dispatch)
{
	if (dispatch->display.len)
		SUPER(dispatch)->history.write(dispatch);
	else
		free(dispatch->display.buffer);
	dispatch->display.buffer = malloc(dispatch->display.buffer_size + 1);
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size + 1);
	dispatch->display.index = 0;
	dispatch->display.indes = 0;
	dispatch->display.len = 0;
	if (dispatch->display.stop && !(dispatch->display.stop = 0))
		write(STDOUT_FILENO, "\n", 1);
	SUPER(dispatch)->display.prompt(NULL, 0, dispatch);
	dispatch->history.index = dispatch->history.count;
}

static inline void	start_error(t_dispatch *const dispatch)
{
	write(STDERR_FILENO, dispatch->foreground.error,
			ft_strlen(dispatch->foreground.error));
	if (dispatch->foreground.error_required_free)
	{
		free(dispatch->foreground.error);
		dispatch->foreground.error_required_free = 0;
	}
	dispatch->foreground.error = NULL;
	SUPER(dispatch)->foreground.destroy(dispatch);
}

void				dispatch_start(t_dispatch *const dispatch)
{
	write(STDOUT_FILENO, "\33[37m\n", sizeof("\33[37m\n"));
	if (dispatch->display.len)
	{
		SUPER(dispatch)->foreground.get(dispatch);
		if (dispatch->foreground.error)
			start_error(dispatch);
		else
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &dispatch->display.saved);
			SUPER(dispatch)->foreground.execute(dispatch);
			SUPER(dispatch)->foreground.destroy(dispatch);
			tcsetattr(STDIN_FILENO, TCSADRAIN, &dispatch->display.current);
			if (dispatch->foreground.background.turn)
			{
				SUPER(dispatch)->sleep(0, 250000000);
				dispatch->foreground.background.turn = 0;
			}
		}
	}
	dispatch_display_routine(dispatch);
}
