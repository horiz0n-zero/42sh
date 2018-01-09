/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenght_unicode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:40:15 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/16 16:41:24 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

static void inline		add_spec(t_printdata *data)
{
	data->len = (uint64_t)data->lenght;
}

static inline void		lenght_unicode_ot(t_printdata *data, const wchar_t uni,
		char *converted)
{
	if (uni < 0x80)
	{
		converted[0] = (char)(uni & 0x7f) | 0x0;
		data->lenght = 1;
	}
	else if (uni < 0x0800)
	{
		converted[0] = (char)((uni >> 6) & 0x1f) | 0xc0;
		converted[1] = (char)(uni & 0x3f) | 0x80;
		data->lenght = 2;
	}
}

void					lenght_unicode(t_printdata *data, va_list *args)
{
	const wchar_t		uni = va_arg(*args, wchar_t);
	char				*converted;

	converted = (void*)&data->data;
	lenght_unicode_ot(data, uni, converted);
	if (uni < 0x010000)
	{
		converted[0] = (char)((uni >> 12) & 0x0f) | 0xe0;
		converted[1] = (char)((uni >> 6) & 0x3f) | 0x80;
		converted[2] = (char)(uni & 0x3f) | 0x80;
		data->lenght = 3;
	}
	else
	{
		converted[0] = (char)((uni >> 18) & 0x07) | 0xf0;
		converted[1] = (char)((uni >> 12) & 0x3f) | 0x80;
		converted[2] = (char)((uni >> 6) & 0x3f) | 0x80;
		converted[3] = (char)(uni & 0x3f) | 0x80;
		data->lenght = 4;
	}
	add_spec(data);
}
