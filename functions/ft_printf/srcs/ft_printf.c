/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:38:20 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/01 10:06:58 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

static void					ft_printfendfunction(const char *const src,
		t_printinfo *const info)
{
	info->total_len--;
	info->data = (uint64_t)write(STDOUT_FILENO, src, info->total_len);
}

int							ft_printf(const char *format, ...)
{
	t_printdata				*element;
	t_printinfo				info;
	va_list					args;

	info.total_len = 1;
	info.data = 0;
	info.function = (void*)ft_printfendfunction;
	va_start(args, format);
	info.args = &args;
	element = NULL;
	info.first_element = &element;
	printf_exec(format, &info, info.first_element);
	va_end(args);
	return ((int)info.total_len);
}
