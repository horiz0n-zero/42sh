/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor_foreground.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:36:21 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 16:00:47 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				ctor_foreground(t_dispatch *const dispatch)
{
	dispatch->foreground.error = NULL;
	dispatch->foreground.error_required_free = 0;
	dispatch->foreground.tokens = NULL;
	dispatch->foreground.index = 0;
	dispatch->foreground.need_task = false;
	dispatch->foreground.wait = WUNTRACED;
	dispatch->foreground.red_mode = S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH;
	SUPER(dispatch)->foreground.collection.ctor(dispatch);
	SUPER(dispatch)->foreground.setsignal(SELF);
	SUPER(dispatch)->foreground.binaries.ctor(dispatch);
	SUPER(dispatch)->foreground.builtins.ctor(dispatch);
	SUPER(dispatch)->foreground.background.ctor(dispatch);
}
