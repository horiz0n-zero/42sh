/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashable_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 16:07:13 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/06 13:25:00 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				*hashablebin_get(t_dispatch *const dispatch,
		const char *src)
{
	const size_t	key = SUPER(dispatch)->foreground.binaries.key(src);
	t_hashpacket	*pos;

	pos = dispatch->foreground.binaries.packets +
		(key % dispatch->foreground.binaries.size);
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
