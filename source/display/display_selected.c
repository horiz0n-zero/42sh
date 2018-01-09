/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_selected.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:05:50 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/04 16:01:20 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void	*insert_backworld(char *dst, const char *backworld)
{
	while (*backworld)
		*dst++ = *backworld++;
	return (dst);
}

static void			pupush(t_dispatch *const dispatch, char *ptr,
		int *const first)
{
	size_t			i;
	char			*src;

	i = 0;
	while (i < dispatch->display.select.count)
	{
		if (dispatch->display.select.array[i].selected)
		{
			src = dispatch->display.select.array[i].name;
			if (dispatch->display.select.app && !*first)
				ptr = insert_backworld(ptr, dispatch->display.select.ref);
			else
				*first = false;
			while (*src)
				*ptr++ = *src++;
			*ptr++ = ' ';
		}
		free(dispatch->display.select.array[i].name);
		i++;
	}
	*ptr = 0;
}

static void			selected_push(t_dispatch *const dispatch, const size_t size)
{
	char *const		buffer = __builtin_alloca(size + 1);
	char			*ptr;
	int				first;

	first = true;
	ptr = buffer;
	pupush(dispatch, ptr, &first);
	while (dispatch->display.buffer_size < dispatch->display.len + size + 1)
		SUPER(dispatch)->display.expand(dispatch);
	SUPER(dispatch)->string.astrpush(buffer, dispatch->display.buffer,
			(int)dispatch->display.index);
}

static inline void	selected(t_dispatch *const dispatch, const size_t size)
{
	selected_push(dispatch, size);
	ft_printf("%s%s%s%s%s %s", CAPS(CR).s, CAPS(CD).s,
			dispatch->display.properties.prompt_color,
			dispatch->display.properties.prompt_string,
			dispatch->display.properties.text_color,
			dispatch->display.buffer);
	dispatch->display.len += size;
	dispatch->display.index += size;
	dispatch->display.select.app = false;
	SUPER(dispatch)->display.goposition(dispatch->display.index, dispatch);
	free(dispatch->display.select.array);
}

void				display_selected(t_dispatch *const dispatch)
{
	size_t			i;
	size_t			size;
	int				first;

	first = true;
	i = 0;
	size = 0;
	while (i < dispatch->display.select.count)
	{
		if (dispatch->display.select.array[i].selected)
		{
			size += dispatch->display.select.array[i].len + 1;
			if (dispatch->display.select.app && !first)
				size += dispatch->display.select.ref_len;
			else
				first = false;
		}
		i++;
	}
	selected(dispatch, size);
}
