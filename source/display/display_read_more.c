/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_read_more.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 14:14:46 by jeblonde          #+#    #+#             */
/*   Updated: 2018/01/05 13:38:39 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				display_read_more(const char *ptr,
		t_dispatch *const dispatch)
{
	const int64_t	data = *(const int64_t*)((const void*)ptr);

	if (data == (int64_t)2117294875)
		SUPER(dispatch)->display.delete(dispatch);
	else if (data == (int64_t)74982532143899)
		SUPER(dispatch)->display.word_right(dispatch);
	else if (data == (int64_t)73883020516123)
		SUPER(dispatch)->display.word_left(dispatch);
	else if (data == (int64_t)71683997260571)
		SUPER(dispatch)->display.line_up(dispatch);
	else if (data == (int64_t)72783508888347)
		SUPER(dispatch)->display.line_down(dispatch);
}
