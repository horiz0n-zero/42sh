/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:38:07 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/01 10:08:09 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

static void				ft_fprintfendfunction(const char *const src,
										t_printinfo *const info)
{
	write((int)info->data, src, info->total_len - 1);
}

void					ft_fprintf(const int fd, const char *format, ...)
{
	t_printdata			*element;
	t_printinfo			info;
	va_list				args;

	element = NULL;
	info.first_element = &element;
	info.function = (void*)ft_fprintfendfunction;
	info.total_len = 1;
	info.data = (uint64_t)fd;
	va_start(args, format);
	info.args = &args;
	printf_exec(format, &info, info.first_element);
	va_end(args);
}
