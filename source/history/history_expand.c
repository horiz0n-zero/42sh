/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 13:47:18 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/05 14:24:04 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				history_expand(t_dispatch *const dispatch)
{
	t_history_node	*array;
	const size_t	csize = sizeof(t_history_node) * dispatch->history.size;

	dispatch->history.size *= 2;
	if (!(array = malloc(sizeof(t_history_node) * dispatch->history.size)))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	SUPER(dispatch)->memory.move((char*)array,
			(const void*)dispatch->history.array, csize);
	free(dispatch->history.array);
	dispatch->history.array = array;
}
