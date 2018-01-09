/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:42:05 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/16 12:55:45 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

static void				push_int(int64_t value, char *dst)
{
	if (!value)
		*dst = '0';
	while (value > 0)
	{
		*dst-- = value % 10 + '0';
		value /= 10;
	}
}

void					transform_uint(t_printdata *data, char *dst)
{
	if (data->flags & MINUS)
	{
		while (data->precision-- > 0)
			*dst++ = '0';
		push_int(data->data, (dst += data->lenght) - 1);
		while (data->width-- > 0)
			*dst++ = ' ';
	}
	else
	{
		while (data->width-- > 0)
			*dst++ = ' ';
		while (data->precision-- > 0)
			*dst++ = '0';
		push_int(data->data, (dst += data->lenght) - 1);
	}
}
