/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toktype_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 10:54:11 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/02 12:25:43 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const int	g_typequote[256] =
{
	[')'] = TOK_PRE,
	['}'] = TOK_SKULL,
	['\"'] = TOK_Q,
	['\''] = TOK_QF,
	['`'] = TOK_INI
};

int					toktype_quote(const char src)
{
	int				v;

	v = g_typequote[(int)src];
	return (v);
}
