/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 10:15:17 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/06 14:54:12 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		var_expand(t_dispatch *const dispatch)
{
	t_var	*new;

	dispatch->var.size *= 2;
	if (!(new = malloc(sizeof(t_variable) * dispatch->var.size)))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	SUPER(dispatch)->memory.move((void*)new, (void*)dispatch->var.local,
			(dispatch->var.size / 2) * sizeof(t_variable));
	free(dispatch->var.local);
	dispatch->var.local = new;
}
