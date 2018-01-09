/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtor_foreground.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:36:28 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 16:00:32 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		dtor_foreground(t_dispatch *const dispatch)
{
	SUPER(dispatch)->foreground.binaries.dtor(dispatch);
	SUPER(dispatch)->foreground.setsignal(DEFAULT);
	SUPER(dispatch)->foreground.background.dtor(dispatch);
	SUPER(dispatch)->foreground.collection.dtor(dispatch);
	SUPER(dispatch)->foreground.builtins.dtor(dispatch);
}
