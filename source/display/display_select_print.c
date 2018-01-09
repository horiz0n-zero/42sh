/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_select_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 09:02:44 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/24 09:50:46 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void	display_select_printer(t_select *s,
		t_dispatch *const dispatch)
{
	if (s->selected)
		write(STDOUT_FILENO, CAPS(US).s, CAPS(US).l);
	if (s->cursor)
		write(STDOUT_FILENO, CAPS(SO).s, CAPS(SO).l);
}

void				display_select_print(t_dispatch *const dispatch)
{
	size_t			index;
	size_t			co;
	t_select		*s;
	size_t			len;

	co = dispatch->display.select.coz;
	index = 0;
	ft_printf("%s\n%s", CAPS(RC).s, CAPS(CD).s);
	while (index < dispatch->display.select.count)
	{
		s = dispatch->display.select.array + index++;
		display_select_printer(s, dispatch);
		ft_printf("%s%s%s", s->bg, s->fg, s->name);
		if (s->selected)
			write(STDOUT_FILENO, CAPS(UE).s, CAPS(UE).l);
		if (s->cursor)
			write(STDOUT_FILENO, CAPS(SE).s, CAPS(SE).l);
		len = dispatch->display.select.len - s->len;
		if (++co % dispatch->display.select.coz == 0)
			write(STDOUT_FILENO, "\n", 1);
		else
			while (len-- > 0)
				write(STDOUT_FILENO, " ", 1);
	}
}
