/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtor_dispatch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:34:19 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 15:38:03 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void			dtor_dispatch(t_dispatch *const dispatch)
{
	SUPER(dispatch)->display.dtor(dispatch);
	SUPER(dispatch)->foreground.dtor(dispatch);
	SUPER(dispatch)->history.dtor(dispatch);
	SUPER(dispatch)->var.dtor(dispatch);
	SUPER(dispatch)->env.dtor(dispatch);
	close(dispatch->string.random);
	if (dispatch->base)
		free(dispatch->base);
	exit(0);
}
