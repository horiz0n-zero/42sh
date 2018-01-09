/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_getstring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 14:58:57 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/30 14:47:45 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void			display_ask(t_dispatch *const dispatch,
		const char *str)
{
	const size_t			len = ft_strlen(str);

	dispatch->display.buffer = malloc(dispatch->display.buffer_size + 1);
	if (!dispatch->display.buffer)
		malloc_exit();
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size + 1);
	dispatch->display.index = 0;
	dispatch->display.indes = len;
	dispatch->display.len = 0;
	write(STDOUT_FILENO, str, len);
	SUPER(dispatch)->display.tmp_loop(dispatch);
}

void						display_getstring(t_dispatch *const dispatch,
		const char *str)
{
	size_t					buffer_size;
	size_t					len;
	char					*tmp;
	char *const				src = dispatch->display.buffer;

	buffer_size = dispatch->display.buffer_size;
	len = dispatch->display.len;
	display_ask(dispatch, str);
	tmp = dispatch->display.buffer;
	dispatch->display.buffer = src;
	dispatch->display.buffer_size ^= buffer_size;
	buffer_size ^= dispatch->display.buffer_size;
	dispatch->display.buffer_size = buffer_size;
	dispatch->display.len ^= len;
	len ^= dispatch->display.len;
	dispatch->display.len ^= len;
	while (len + dispatch->display.len >= dispatch->display.buffer_size)
		SUPER(dispatch)->display.expand(dispatch);
	SUPER(dispatch)->memory.move(dispatch->display.buffer +
			dispatch->display.len, tmp, len);
	dispatch->display.len += len;
	free(tmp);
}
