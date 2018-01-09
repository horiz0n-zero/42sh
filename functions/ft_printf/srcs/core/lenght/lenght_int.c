/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenght_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:39:07 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/16 11:40:39 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

static const int64_t	g_cut[8] =
{
	[1] = 0xFF,
	[2] = 0xFFFF,
	[3] = 0xFFFFFF,
	[4] = 0xFFFFFFFF,
};

static uint64_t			int_len(int64_t value)
{
	uint64_t			len;

	len = 0;
	if (value < 0)
		value = -value;
	else if (!value)
		return (1);
	while (value > 0)
	{
		value /= 10;
		len++;
	}
	return (len);
}

static void				add_spec(t_printdata *data)
{
	if (data->data < 0)
		data->len++;
	else
	{
		if (data->flags & (PLUS | SPACE))
			data->len++;
	}
}

void					lenght_int(t_printdata *data, va_list *args)
{
	uint64_t			len;

	if (!data->lenght)
		data->data = (int64_t)va_arg(*args, int32_t) & 0xFFFFFFFF;
	else if (data->lenght <= 4)
		data->data = ((int64_t)va_arg(*args, int32_t)) & g_cut[data->lenght];
	else
		data->data = va_arg(*args, int64_t);
	len = int_len(data->data);
	data->lenght = (uint32_t)len;
	if (data->precision > len)
		data->precision -= len;
	else
		data->precision = 0;
	data->len = data->precision + len;
	if (data->width > data->len)
	{
		data->width -= data->len;
		data->len += data->width;
	}
	else
		data->width = 0;
	add_spec(data);
}
