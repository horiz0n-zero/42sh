/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:41:51 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/16 12:52:15 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

static void			pointer_push(uint64_t value, char *dst)
{
	static char		board[] =
	{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e',
		'f'};

	if (!value)
	{
		*dst = '0';
		return ;
	}
	while (value)
	{
		*dst-- = board[value % 16];
		value /= 16;
	}
}

void				transform_pointer(t_printdata *data, char *dst)
{
	if (data->flags & MINUS)
	{
		*dst++ = '0';
		*dst++ = 'x';
		while (data->precision-- > 0)
			*dst++ = '0';
		pointer_push((uint64_t)data->data, (dst += data->lenght) - 1);
		while (data->width-- > 0)
			*dst++ = ' ';
	}
	else
	{
		while (data->width-- > 0)
			*dst++ = ' ';
		*dst++ = '0';
		*dst++ = 'x';
		while (data->precision-- > 0)
			*dst++ = '0';
		pointer_push((uint64_t)data->data, (dst += data->lenght) - 1);
	}
}
