/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtor_hashablebin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 12:53:47 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/07 11:42:53 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void					dtor_hashablebin(t_dispatch *const dispatch)
{
	t_hashpacket		*packets;
	t_hashpacket		*target;
	void				*tmp;

	packets = dispatch->foreground.binaries.packets;
	while (dispatch->foreground.binaries.size-- > 0)
	{
		target = packets++;
		if (target)
		{
			free(target->element);
			free(target->src);
		}
		target = target->next;
		while (target)
		{
			tmp = target;
			free(target->element);
			free(target->src);
			target = target->next;
			free(tmp);
		}
	}
	free(dispatch->foreground.binaries.packets);
}
