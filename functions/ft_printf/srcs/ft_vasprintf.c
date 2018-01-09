/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vasprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 12:30:24 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/01 10:12:04 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"
#include <stdlib.h>

static void				ft_vasprintf_endfunc(const char *const src,
		t_printinfo *const info)
{
	char				*new;
	int					index;

	index = 0;
	new = malloc(sizeof(char) * info->total_len--);
	while (index < (int)info->total_len)
	{
		new[index] = src[index];
		index++;
	}
	new[info->total_len] = 0;
	info->data = (uint64_t)new;
}

void					ft_vasprintf(char **dst, const char *format, ...)
{
	t_printdata			*element;
	t_printinfo			info;
	va_list				args;

	info.total_len = 1;
	element = NULL;
	info.first_element = &element;
	info.function = (void*)ft_vasprintf_endfunc;
	info.data = 0;
	va_start(args, format);
	info.args = &args;
	printf_exec(format, &info, info.first_element);
	va_end(args);
	*dst = (char*)info.data;
}
