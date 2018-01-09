/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_get_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:38:46 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/16 16:31:58 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

static const uint32_t	g_conversion[256] =
{
	['\0'] = PRINT_ERROR,
	['%'] = PRINT_PERCENT,
	['s'] = PRINT_S,
	['S'] = PRINT_SS,
	['p'] = PRINT_P,
	['d'] = PRINT_D,
	['D'] = PRINT_DD,
	['i'] = PRINT_I,
	['o'] = PRINT_O,
	['O'] = PRINT_OO,
	['u'] = PRINT_U,
	['U'] = PRINT_UU,
	['x'] = PRINT_X,
	['X'] = PRINT_XX,
	['c'] = PRINT_C,
	['C'] = PRINT_CC
};

static const uint32_t	g_flags[256] =
{
	['-'] = MINUS,
	['+'] = PLUS,
	[' '] = SPACE,
	['0'] = ZERO,
	['#'] = HASH
};

static const bool		g_lenght[256] =
{
	['h'] = true,
	['l'] = true,
	['j'] = true,
	['z'] = true
};

static uint32_t			get_lenght(const char *const src,
		uint32_t index, uint32_t *const lenght)
{
	const char		f = src[index];
	const char		s = src[index + 1];

	if (f == 'h')
	{
		if (s == 'h')
			*lenght = sizeof(char);
		else
			*lenght = sizeof(short);
	}
	else if (f == 'l')
	{
		if (s == 'l')
			*lenght = sizeof(long);
		else
			*lenght = sizeof(long long);
	}
	else if (f == 'j')
		*lenght = sizeof(intmax_t);
	else if (f == 'z')
		*lenght = sizeof(size_t);
	while (g_lenght[(int)src[index]])
		index++;
	return (index);
}

void					printf_get_data(const char *const src,
		uint32_t *const index_ptr, t_printdata *data)
{
	uint32_t			index;

	index = *index_ptr;
	while (g_flags[(int)src[index]])
		data->flags |= g_flags[(int)src[index++]];
	if (src[index] >= '0' && src[index] <= '9')
		index = atoi_print(&data->width, src, index);
	if (src[index] == '.')
	{
		while (src[index] == '.' && ++index)
			data->flags |= POINT;
		index = atoi_print(&data->precision, src, index);
	}
	index = get_lenght(src, index, &data->lenght);
	while (src[index] && (g_lenght[(int)src[index]] || g_flags[(int)src[index]]
				|| src[index] == '.'))
	{
		if (g_flags[(int)src[index]])
			data->flags |= g_flags[(int)src[index]];
		index++;
	}
	if (g_conversion[(int)src[index]])
		data->conversion = g_conversion[(int)src[index++]];
	*index_ptr = index;
	data->end_index = index;
}
