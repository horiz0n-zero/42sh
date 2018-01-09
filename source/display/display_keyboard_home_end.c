/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_keyboard_home_end.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 14:23:39 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/02 14:23:45 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void			display_home(t_dispatch *const dispatch)
{
	while (dispatch->display.index > 0)
		SUPER(dispatch)->display.left(dispatch);
}

void			display_end(t_dispatch *const dispatch)
{
	while (dispatch->display.index < dispatch->display.len)
		SUPER(dispatch)->display.right(dispatch);
}
