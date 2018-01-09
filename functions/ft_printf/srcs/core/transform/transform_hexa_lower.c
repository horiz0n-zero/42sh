/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_hexa_lower.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:40:53 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/16 16:35:08 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

static const char	g_lower[16] =
{
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'a', 'b', 'c', 'd', 'e', 'f'
};

static void			push_hexa(t_printdata *data, char *dst)
{
	uint64_t		value;

	value = (uint64_t)data->data;
	if (!value)
	{
		if (data->flags & POINT && !data->precision)
			return ;
		else
			*dst = '0';
	}
	while (value)
	{
		*dst-- = g_lower[value % 16];
		value /= 16;
	}
}

void				transform_hexa_lower(t_printdata *data, char *dst)
{
	const char		pad = !data->precision && data->flags & ZERO ? '0' : ' ';

	if (data->flags & MINUS)
	{
		if (data->flags & HASH && data->data)
		{
			*dst++ = '0';
			*dst++ = 'x';
		}
		while (data->precision && data->precision--)
			*dst++ = '0';
		push_hexa(data, (dst += data->lenght) - 1);
		while (data->width-- > 0)
			*dst++ = ' ';
	}
	else
	{
		while (data->width-- > 0)
			*dst++ = pad;
		if (data->flags & HASH && data->data && (*dst++ = '0'))
			*dst++ = 'x';
		while (data->precision && data->precision--)
			*dst++ = '0';
		push_hexa(data, (dst += data->lenght) - 1);
	}
}
