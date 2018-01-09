/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenght_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:39:52 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/16 11:44:44 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

static uint64_t		ft_strlen(const char *const src)
{
	uint64_t		len;

	len = 0;
	while (src[len])
		len++;
	return (len);
}

void				lenght_string(t_printdata *data, va_list *args)
{
	const char		*ptr;
	uint64_t		len;

	ptr = va_arg(*args, const char*);
	if (!ptr)
	{
		len = sizeof("(null)");
		ptr = "(null)";
	}
	else
		len = ft_strlen(ptr);
	if (!data->precision)
		data->precision = len;
	else if (data->precision > len)
		data->precision = len;
	if (data->width >= len)
	{
		data->len = data->width;
		data->width -= data->precision;
	}
	else
		data->len = len;
	data->data = (int64_t)ptr;
}
