/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:40:46 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/16 12:48:45 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

void				transform_char(t_printdata *data, char *dst)
{
	const char		pad = data->flags & ZERO ? '0' : ' ';
	const char		c = (char)data->data;

	if (data->flags & MINUS)
	{
		*dst++ = c;
		while (data->width--)
			*dst++ = ' ';
	}
	else
	{
		while (data->width-- > 1)
			*dst++ = pad;
		*dst = c;
	}
}
