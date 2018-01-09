/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:41:39 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/16 12:51:12 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

void				transform_percent(t_printdata *data, char *dst)
{
	const char		pad = data->flags & ZERO ? '0' : ' ';

	if (data->flags & MINUS)
	{
		*dst++ = '%';
		while (data->width-- > 0)
			*dst++ = ' ';
	}
	else
	{
		while (data->width-- > 1)
			*dst++ = pad;
		*dst = '%';
	}
}
