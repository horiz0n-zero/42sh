/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:06:25 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/05 13:21:27 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void					*search_inhistory(register t_dispatch *const d)
{
	register t_history_node	*ptr;
	size_t					i;

	i = 0;
	ptr = d->history.array;
	while (i++ < d->history.count)
	{
		if (SUPER(d)->string.strinstr(ptr->src, d->display.buffer))
			return (ptr->src);
		ptr++;
	}
	return ("");
}

static int					search_tabulation(t_dispatch *const dispatch,
		char *const result)
{
	const size_t			len = ft_strlen(result);

	while (len + 1 > dispatch->display.buffer_size)
		SUPER(dispatch)->display.expand(dispatch);
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size);
	SUPER(dispatch)->memory.move(dispatch->display.buffer, result, len);
	dispatch->display.len = len;
	dispatch->display.index = len;
	ft_printf("%s%s%s\n%s>> %s", CAPS(RC).s, CAPS(CD).s, result,
	dispatch->display.properties.prompt_color, dispatch->display.buffer);
	SUPER(dispatch)->display.goposition(dispatch->display.index, dispatch);
	return (true);
}

static const t_readfunc		g_reads[] =
{
	display_read_one,
	display_read_one,
	display_read_more,
	display_read_three,
	display_read_more,
	display_read_more,
	display_read_more,
	display_read_more,
	display_read_more
};

static void					search_loop(t_dispatch *const dispatch, char **ret)
{
	int64_t					data;
	char *const				ptr = (void*)&data;
	ssize_t					size;
	char					*result;

	result = NULL;
	while (42)
	{
		size = read(STDIN_FILENO, ptr, sizeof(int64_t));
		if (size == 1)
		{
			if (*ptr == 13)
				break ;
			if (*ptr == 9 && search_tabulation(dispatch, result))
				continue ;
		}
		g_reads[size](ptr, dispatch);
		result = search_inhistory(dispatch);
		ft_printf("%s%s%s\n%s>> %s", CAPS(RC).s, CAPS(CD).s, result,
			dispatch->display.properties.prompt_color,
			dispatch->display.buffer);
		SUPER(dispatch)->display.goposition(dispatch->display.index, dispatch);
	}
	*ret = result;
}

void						history_search(t_dispatch *const dispatch)
{
	const size_t			indes = dispatch->display.indes;
	char					*result;
	size_t					len;

	SUPER(dispatch)->display.goposition(0, dispatch);
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size + 1);
	dispatch->display.len = 0;
	dispatch->display.indes = sizeof(">> ") - 1;
	ft_printf("%s\n%s\33[%zdC%s%s%s%s", CAPS(CD).s, CAPS(UP).s, indes,
			CAPS(SC).s, CAPS(DO).s, dispatch->display.properties.prompt_color,
			">> ");
	search_loop(dispatch, &result);
	ft_printf("%s%s%s", CAPS(RC).s, CAPS(CD).s, result);
	dispatch->display.indes = indes;
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size + 1);
	len = ft_strlen(result);
	while (len + 1 > dispatch->display.buffer_size)
		SUPER(dispatch)->display.expand(dispatch);
	SUPER(dispatch)->memory.move(dispatch->display.buffer, result, len);
	dispatch->display.len = len;
	dispatch->display.index = len;
}
