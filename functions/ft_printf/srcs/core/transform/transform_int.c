/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:41:19 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/16 12:49:47 by jeblonde         ###   ########.fr       */
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

static inline void		*add_spec(t_printdata *const data, char *dst)
{
	if (data->data < 0)
	{
		data->data = -data->data;
		*dst++ = '-';
	}
	else
	{
		if (data->flags & PLUS)
			*dst++ = '+';
		else if (data->flags & SPACE)
			*dst++ = ' ';
	}
	return (dst);
}

void					transform_int(t_printdata *data, char *dst)
{
	if (data->flags & MINUS)
	{
		dst = add_spec(data, dst);
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
		dst = add_spec(data, dst);
		while (data->precision-- > 0)
			*dst++ = '0';
		push_int(data->data, (dst += data->lenght) - 1);
	}
}
