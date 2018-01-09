/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashbuiltins_dtor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 15:48:46 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/07 10:53:02 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				dtor_hashbuiltins(t_dispatch *const dispatch)
{
	t_hashpacket	*pos;
	t_hashpacket	*ptr;
	void			*tmp;

	pos = dispatch->foreground.builtins.packets;
	while (dispatch->foreground.builtins.size-- > 0)
	{
		ptr = pos++;
		while (ptr && ptr->next)
		{
			tmp = ptr->next;
			ptr = ptr->next->next;
			free(tmp);
		}
	}
	free(dispatch->foreground.builtins.packets);
}
