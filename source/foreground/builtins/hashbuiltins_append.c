/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashbuiltins_append.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 15:50:17 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/07 10:44:36 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				hashbuiltins_append(t_dispatch *const dispatch,
		char *src, void *const element)
{
	const size_t	key = SUPER(dispatch)->foreground.builtins.key(src);
	t_hashpacket	*pos;

	pos = dispatch->foreground.builtins.packets +
		(key % dispatch->foreground.builtins.size);
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
		return ;
	}
	pos->src = src;
	pos->element = element;
	pos->next = NULL;
}
