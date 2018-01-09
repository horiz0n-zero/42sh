/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toktype_sep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 10:46:21 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 16:33:08 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const int	g_typesep[256] =
{
	['>'] = TOK_RED,
	['<'] = TOK_RED,
	['|'] = TOK_OR,
	['&'] = TOK_AND,
	[';'] = TOK_COMMA
};

int					toktype_sep(const char *src, int len)
{
	int				v;

	v = 0;
	while (len--)
		v |= g_typesep[(int)*src++];
	return (v);
}
