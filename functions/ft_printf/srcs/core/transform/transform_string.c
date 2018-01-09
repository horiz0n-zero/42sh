/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:41:58 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/16 12:52:25 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

void				transform_string(t_printdata *data, char *dst)
{
	const char		pad = data->flags & ZERO ? '0' : ' ';
	const char		*ptr = (char*)data->data;

	if (data->flags & MINUS)
	{
		while (data->precision-- > 0)
			*dst++ = *ptr++;
		while (data->width-- > 0)
			*dst++ = ' ';
	}
	else
	{
		while (data->width-- > 0)
			*dst++ = pad;
		while (data->precision-- > 0)
			*dst++ = *ptr++;
	}
}
