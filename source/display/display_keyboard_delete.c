/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_keyboard_delete.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 14:23:53 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/02 14:23:55 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		display_delete(t_dispatch *const dispatch)
{
	if (dispatch->display.index < dispatch->display.len)
	{
		SUPER(dispatch)->display.right(dispatch);
		SUPER(dispatch)->display.remove(dispatch);
	}
}
