/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_toksplit_count.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 11:36:51 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/05 13:54:03 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const int		g_tokcor[256] =
{
	[' '] = 1,
	['\n'] = 1,
	['\t'] = 1,
	[';'] = 2,
	['|'] = 2,
	['&'] = 2,
	['>'] = 2,
	['<'] = 2,
	['{'] = '}',
	['('] = ')',
	['\"'] = '\"',
	['\''] = '\'',
	['`'] = '`'
};

static inline int		tok_common(register t_dispatch *const dispatch,
		register int i)
{
	while (BUFFER(i) && !g_tokcor[(int)BUFFER(i)])
	{
		if (BUFFER(i) == '\\')
		{
			if (BUFFER(++i))
				i++;
			else
			{
				SUPER(dispatch)->string.kpush(dispatch->display.buffer, i);
				dispatch->display.len--;
				SUPER(dispatch)->display.gettxt(dispatch, "> ");
			}
		}
		else
			i++;
	}
	return (i);
}

static inline int		tok_separator(register t_dispatch *const dispatch,
		register int i)
{
	while (BUFFER(i) && g_tokcor[(int)BUFFER(i)] == 2)
		i++;
	return (i);
}

static inline int		tok_quotes(register t_dispatch *const dispatch,
		register int i)
{
	const char			raw = (char)g_tokcor[(int)BUFFER(i++)];

	while (1)
	{
		while (BUFFER(i) && BUFFER(i) != raw)
			i++;
		if (!BUFFER(i))
		{
			SUPER(dispatch)->display.getctxt(dispatch, raw);
			if (dispatch->display.stop)
				break ;
		}
		else if (BUFFER(i) == raw && BUFFER(i - 1) != '\\')
			break ;
		else
			i++;
	}
	return (++i);
}

size_t					string_toksplit_count(
		register t_dispatch *const dispatch)
{
	size_t				count;
	register int		i;
	int					type;

	i = 0;
	count = 1;
	while (BUFFER(i))
	{
		while (BUFFER(i) && g_tokcor[(int)BUFFER(i)] == 1)
			i++;
		if (!BUFFER(i))
			break ;
		count++;
		type = g_tokcor[(int)BUFFER(i)];
		if (!type)
			i = tok_common(dispatch, i);
		else if (type == 2)
			i = tok_separator(dispatch, i);
		else
			i = tok_quotes(dispatch, i);
		if (dispatch->display.stop)
			return (0);
	}
	return (count);
}
