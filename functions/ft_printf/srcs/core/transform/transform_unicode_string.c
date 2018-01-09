/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_unicode_string.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:42:19 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/16 12:53:06 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

static void				*push_four(char *dst, const wchar_t uni)
{
	*dst++ = (char)((uni >> 18) & 0x07) | 0xf0;
	*dst++ = (char)((uni >> 12) & 0x3f) | 0x80;
	*dst++ = (char)((uni >> 6) & 0x3f) | 0x80;
	*dst++ = (char)(uni & 0x3f) | 0x80;
	return (dst);
}

static void				*push_three(char *dst, const wchar_t uni)
{
	*dst++ = (char)((uni >> 12) & 0x0f) | 0xe0;
	*dst++ = (char)((uni >> 6) & 0x3f) | 0x80;
	*dst++ = (char)(uni & 0x3f) | 0x80;
	return (dst);
}

static void				*push_two(char *dst, const wchar_t uni)
{
	*dst++ = (char)((uni >> 6) & 0x1f) | 0xc0;
	*dst++ = (char)(uni & 0x3f) | 0x80;
	return (dst);
}

static void				*push_one(char *dst, const wchar_t uni)
{
	*dst++ = (char)(uni & 0x7f) | 0x0;
	return (dst);
}

void					transform_unicode_string(t_printdata *data, char *dst)
{
	wchar_t				*ptr;

	ptr = (void*)data->data;
	while (*ptr)
	{
		if (*ptr < 0x80)
			dst = push_one(dst, *ptr);
		else if (*ptr < 0x0800)
			dst = push_two(dst, *ptr);
		else if (*ptr < 0x010000)
			dst = push_three(dst, *ptr);
		else
			dst = push_four(dst, *ptr);
		ptr++;
	}
}
