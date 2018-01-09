/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashalias_dtor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 13:57:47 by afeuerst          #+#    #+#             */
/*   Updated: 2017/10/30 09:08:55 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void			free_array(char **array)
{
	while (*array)
		free(*array++);
}

void				dtor_hashalias(t_dispatch *const dispatch)
{
	t_hashpacket	*pos;
	size_t			index;

	index = 0;
	while (index < dispatch->foreground.alias.size)
	{
		pos = dispatch->foreground.alias.packets + index++;
		while (pos)
		{
			if (pos->src)
				free(pos->src);
			if (pos->element)
				free_array(pos->element);
			pos = pos->next;
		}
	}
	free(dispatch->foreground.alias.packets);
	close(dispatch->foreground.aliasfile);
	free(dispatch->foreground.aliaspath);
}
