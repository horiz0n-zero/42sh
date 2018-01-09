/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenght_unicode_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:40:24 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/16 11:47:35 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

void					lenght_unicode_string(t_printdata *data, va_list *args)
{
	wchar_t				*ptr;

	ptr = va_arg(*args, wchar_t*);
	if (!ptr)
	{
		ptr = (void*)"(null)";
		data->len = sizeof("(null)");
		data->data = (int64_t)ptr;
	}
	else
	{
		data->data = (int64_t)ptr;
		while (*ptr)
		{
			if (*ptr < 0x80)
				data->len++;
			else if (*ptr < 0x0800)
				data->len += 2;
			else if (*ptr < 0x010000)
				data->len += 3;
			else
				data->len += 4;
			ptr++;
		}
	}
}
