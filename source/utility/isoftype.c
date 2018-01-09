/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isoftype.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 12:53:10 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/22 16:29:46 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static int			g_spec[256] =
{
	['&'] = 1,
	['|'] = 1,
	['<'] = 1,
	['>'] = 1
};

static inline int	is_and(const char c2, const char c3)
{
	if (!g_spec[(int)c2])
		return (TYPE_AND);
	else if (c2 == '&' && !g_spec[(int)c3])
		return (TYPE_ANDAND);
	else if (c2 == '>' && !g_spec[(int)c3])
		return (TYPE_AR);
	else if (c2 == '<' && !g_spec[(int)c3])
		return (TYPE_AL);
	return (TYPE_ERROR);
}

static inline int	is_or(const char c2, const char c3)
{
	if (!g_spec[(int)c2])
		return (TYPE_OR);
	else if (c2 == '|' && !g_spec[(int)c3])
		return (TYPE_OROR);
	return (TYPE_ERROR);
}

static inline int	is_r(const char c2, const char c3)
{
	if (!g_spec[(int)c2])
		return (TYPE_L);
	else if (c2 == '<' && !g_spec[(int)c3])
		return (TYPE_LL);
	else if (c2 == '<' && c3 == '<')
		return (TYPE_LLL);
	else if (c2 == '&' && !g_spec[(int)c3])
		return (TYPE_LA);
	else if (c2 == '>' && !g_spec[(int)c3])
		return (TYPE_IO);
	return (TYPE_ERROR);
}

int					isoftype(const char *const src)
{
	const char	f = *src;
	const char	s = *(src + 1);
	const char	t = *(src + 2);

	if (f == '&')
		return (is_and(s, t));
	else if (f == '|')
		return (is_or(s, t));
	else if (f == '<')
		return (is_r(s, t));
	else if (f == '>')
	{
		if (!g_spec[(int)s])
			return (TYPE_R);
		else if (s == '>' && !g_spec[(int)t])
			return (TYPE_RR);
		else if (s == '&' && !g_spec[(int)t])
			return (TYPE_RA);
		else
			return (TYPE_ERROR);
	}
	else if (f == ';')
		if (s != ';')
			return (TYPE_COMMA);
	return (TYPE_ERROR);
}
