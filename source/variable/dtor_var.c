/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtor_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 10:13:09 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/06 13:06:00 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		dtor_var(t_dispatch *const dispatch)
{
	size_t	i;

	i = 0;
	while (i < dispatch->var.count)
	{
		if (dispatch->var.local[i].key)
			free(dispatch->var.local[i].key);
		i++;
	}
	free(dispatch->var.local);
}
