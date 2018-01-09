/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toktype_common.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 15:07:53 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/11 16:02:45 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const int	g_tokcommon[256] =
{
	['*'] = TOK_GLOB,
	['?'] = TOK_GLOB,
	[']'] = TOK_GLOB,
	['['] = TOK_GLOB,
	['$'] = TOK_NEEDP | TOK_DOLLAR,
	['~'] = TOK_NEEDP,
	['='] = TOK_EQUAL
};

int					toktype_common(const char *src)
{
	int				v;

	v = 0;
	while (*src)
		v |= g_tokcommon[(int)*src++];
	return (v);
}
