/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 15:12:44 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/01 13:08:46 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		display_expand(t_dispatch *const dispatch)
{
	char	*new;

	dispatch->display.buffer_size *= 2;
	new = malloc(dispatch->display.buffer_size + 1);
	if (!new)
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	ft_memset(new, dispatch->display.buffer_size + 1);
	SUPER(dispatch)->memory.move(new, dispatch->display.buffer,
			dispatch->display.len);
	free(dispatch->display.buffer);
	dispatch->display.buffer = new;
}
