/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 10:10:18 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/04 11:30:43 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				ctor_var(t_dispatch *const dispatch)
{
	int				i;

	i = 0;
	dispatch->var.size = 32;
	dispatch->var.count = 0;
	dispatch->var.local = malloc(sizeof(t_variable) * dispatch->var.size);
	if (!dispatch->var.local)
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
}
