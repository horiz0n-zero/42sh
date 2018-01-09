/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 14:06:15 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 15:33:43 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static int			history_push(t_dispatch *const dispatch,
		const int *const nb, int i)
{
	size_t			len;
	int				index;

	if (nb[0] < 0 || nb[0] >= (int)dispatch->history.count)
		return (i);
	if (nb[1])
		index = (int)dispatch->history.count - nb[0];
	else
		index = nb[0];
	len = ft_strlen(dispatch->history.array[index].src);
	while (dispatch->display.buffer_size < len + dispatch->display.len + 1)
		SUPER(dispatch)->display.expand(dispatch);
	SUPER(dispatch)->string.astrpush(dispatch->history.array[index].src,
			dispatch->display.buffer, i);
	i += (int)len;
	dispatch->display.len += len;
	return (i);
}

static inline void	display_rm(t_dispatch *const dispatch, const int i)
{
	SUPER(dispatch)->string.kpush(dispatch->display.buffer, i);
	dispatch->display.len--;
	if (dispatch->display.index)
		dispatch->display.index--;
}

static int			history_look(t_dispatch *const dispatch, int i)
{
	int				nb[2];

	nb[0] = 0;
	nb[1] = false;
	if (BUFFER(i + 1) == '-' && (nb[1] = true) && dispatch->display.len--)
		SUPER(dispatch)->string.kpush(dispatch->display.buffer, i);
	if (BUFFER(i + 1) == '!')
	{
		nb[0] = (int)dispatch->history.count - 1;
		display_rm(dispatch, i);
		display_rm(dispatch, i);
		return (history_push(dispatch, nb, i));
	}
	display_rm(dispatch, i);
	while (BUFFER(i) >= '0' && BUFFER(i) <= '9')
	{
		nb[0] = nb[0] * 10 + (BUFFER(i) - '0');
		display_rm(dispatch, i);
	}
	i = history_push(dispatch, nb, i);
	return (i);
}

void				foreground_history(t_dispatch *const dispatch)
{
	register int	i;
	int				isqf;

	i = 0;
	isqf = false;
	while (BUFFER(i))
	{
		if (BUFFER(i) == '\'')
		{
			isqf = isqf ? false : true;
			i++;
			continue ;
		}
		if (BUFFER(i) == '!' && !isqf)
		{
			if ((BUFFER(i + 1) >= '0' && BUFFER(i + 1) <= '9') ||
					BUFFER(i + 1) == '-' || BUFFER(i + 1) == '!')
				i = history_look(dispatch, i);
			else
				i++;
		}
		else
			i++;
	}
}
