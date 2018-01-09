/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenght_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:39:44 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/16 11:44:26 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

static uint64_t		pointer_len(uint64_t value)
{
	uint64_t		len;

	len = 0;
	if (!value)
		return (1);
	while (value)
	{
		value /= 16;
		len++;
	}
	return (len);
}

void				lenght_pointer(t_printdata *data, va_list *args)
{
	uint64_t		len_value;

	data->data = (int64_t)va_arg(*args, void*);
	len_value = pointer_len((uint64_t)data->data);
	if (data->precision > len_value)
		data->precision -= len_value;
	else
		data->precision = 0;
	data->len = len_value + 2 + data->precision;
	if (data->width > data->len)
	{
		data->width = data->width - data->len;
		data->len += data->width;
	}
	else
		data->width = 0;
	data->lenght = (uint32_t)len_value;
}
