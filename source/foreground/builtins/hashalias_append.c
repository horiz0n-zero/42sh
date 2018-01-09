/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashalias_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:58:52 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/06 13:07:49 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				hashalias_append(t_dispatch *const dispatch, char *src,
		void *const element)
{
	const size_t	key = SUPER(dispatch)->foreground.alias.key(src);
	t_hashpacket	*pos;

	pos = dispatch->foreground.alias.packets + (key %
			dispatch->foreground.alias.size);
	if (pos->src)
	{
		while (pos->next)
			pos = pos->next;
		pos->next = malloc(sizeof(t_hashpacket));
		if (!pos->next)
			SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
		pos = pos->next;
		pos->src = src;
		pos->element = element;
		pos->next = NULL;
	}
	else
	{
		pos->src = src;
		pos->element = element;
	}
}
