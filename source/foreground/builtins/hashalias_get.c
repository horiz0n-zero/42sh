/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashalias_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:03:19 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/06 13:08:05 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				*hashalias_get(t_dispatch *const dispatch, const char *src)
{
	const size_t	key = SUPER(dispatch)->foreground.alias.key(src);
	t_hashpacket	*pos;

	if (!dispatch->foreground.aliaspath)
		return (NULL);
	pos = dispatch->foreground.alias.packets + (key %
			dispatch->foreground.alias.size);
	if (pos->src)
	{
		while (1)
		{
			if (!ft_strcmp(pos->src, src))
				return (pos->element);
			pos = pos->next;
			if (!pos)
				return (NULL);
		}
	}
	return (NULL);
}
