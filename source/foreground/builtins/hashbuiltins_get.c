/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashbuiltins_get.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 15:51:52 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/05 13:21:00 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				*hashbuiltins_get(t_dispatch *const dispatch,
		const char *src)
{
	const size_t	key = SUPER(dispatch)->foreground.builtins.key(src);
	t_hashpacket	*pos;

	pos = dispatch->foreground.builtins.packets +
		(key % dispatch->foreground.builtins.size);
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
