/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_getsplit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 13:29:26 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/05 11:47:16 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void			display_ask(t_dispatch *const dispatch,
		const char *const src)
{
	dispatch->display.buffer = malloc(dispatch->display.buffer_size + 1);
	if (!dispatch->display.buffer)
		malloc_exit();
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size + 1);
	dispatch->display.index = 0;
	dispatch->display.indes = ft_strlen(src);
	dispatch->display.len = 0;
	write(STDOUT_FILENO, src, dispatch->display.indes);
	SUPER(dispatch)->display.tmp_loop(dispatch);
}

void						display_gettxt(t_dispatch *const dispatch,
		const char *const pr)
{
	size_t					buffer_size;
	size_t					len;
	char					*tmp;
	char *const				src = dispatch->display.buffer;

	buffer_size = dispatch->display.buffer_size;
	len = dispatch->display.len;
	display_ask(dispatch, pr);
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

static inline void			display_cask(t_dispatch *const dispatch,
		const char c)
{
	dispatch->display.buffer = malloc(dispatch->display.buffer_size + 1);
	if (!dispatch->display.buffer)
		malloc_exit();
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size + 1);
	dispatch->display.index = 0;
	dispatch->display.indes = REQ_QUOTES_SIZE;
	dispatch->display.len = 0;
	ft_printf(REQ_QUOTES, c);
	SUPER(dispatch)->display.tmp_loop(dispatch);
}

void						display_getctxt(t_dispatch *const dispatch,
		const char c)
{
	size_t					buffer_size;
	size_t					len;
	char					*tmp;
	char *const				src = dispatch->display.buffer;

	buffer_size = dispatch->display.buffer_size;
	len = dispatch->display.len;
	display_cask(dispatch, c);
	tmp = dispatch->display.buffer;
	dispatch->display.buffer = src;
	dispatch->display.buffer_size ^= buffer_size;
	buffer_size ^= dispatch->display.buffer_size;
	dispatch->display.buffer_size = buffer_size;
	dispatch->display.len ^= len;
	len ^= dispatch->display.len;
	dispatch->display.len ^= len;
	while (len + 1 + dispatch->display.len >= dispatch->display.buffer_size)
		SUPER(dispatch)->display.expand(dispatch);
	SUPER(dispatch)->memory.move(dispatch->display.buffer +
			dispatch->display.len, tmp, len);
	dispatch->display.len += len;
	free(tmp);
}
