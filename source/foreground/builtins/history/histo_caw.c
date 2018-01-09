/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histo_caw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 10:53:25 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 14:34:47 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int						histo_c(t_dispatch *const dispatch)
{
	t_history_node		*ptr;

	ptr = dispatch->history.array;
	while (dispatch->history.count-- > 0)
	{
		free(ptr->src);
		ptr++;
	}
	dispatch->history.index = 0;
	dispatch->history.count = 0;
	close(dispatch->history.guard);
	dispatch->history.guard = open(ft_stcjoin(dispatch->base, "_history"),
	O_TRUNC | O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
	return (1);
}

int						histo_a(t_dispatch *const dispatch)
{
	t_history_node		*ptr;

	ptr = dispatch->history.array;
	while (dispatch->history.count-- > 0)
	{
		free(ptr->src);
		ptr++;
	}
	free(dispatch->history.array);
	SUPER(dispatch)->history.ctor(dispatch);
	return (1);
}

int						histo_w(t_dispatch *const dispatch)
{
	SUPER(dispatch)->history.dtor(dispatch);
	SUPER(dispatch)->history.ctor(dispatch);
	return (1);
}
