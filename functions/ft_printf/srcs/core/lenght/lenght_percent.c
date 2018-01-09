/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenght_percent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:39:37 by afeuerst          #+#    #+#             */
/*   Updated: 2017/08/23 13:39:38 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

void					lenght_percent(t_printdata *data, va_list *args)
{
	data->data = ((int64_t)va_arg(*args, int)) & 0xFF;
	if (data->width)
		data->len = data->width;
	else
		data->len = 1;
}
