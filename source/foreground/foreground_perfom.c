/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_perfom.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 10:01:29 by jeblonde          #+#    #+#             */
/*   Updated: 2017/12/17 15:56:35 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void		perfom_globing(t_dispatch *const dispatch)
{
	size_t				size;
	t_token				*new;

	new = SUPER(dispatch)->foreground.globing(TOKENSRC, &size);
	if (!size)
		return (free(new));
	ktoken(dispatch->foreground.tokens, dispatch->foreground.index, true);
	tokensinsert(dispatch, new);
	free(new);
}

static const t_perfom	g_perfoms[256] =
{
	['$'] = {1, dollar_len, dollar_push},
	['~'] = {1, home_len, home_push}
};

static inline void		perfom_common_replace(t_dispatch *const dispatch,
		const size_t size)
{
	char				*new;
	char				*src;

	src = TOKENSRC;
	if (!(new = malloc(size + 1)))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	while (*src)
	{
		if (g_perfoms[(int)*src].index)
			new = g_perfoms[(int)*src].func_push(dispatch, &src, new);
		else
			*new++ = *src++;
	}
	*new = 0;
	free(TOKENSRC);
	TOKENSRC = new - size;
}

static inline void		perfom_common(t_dispatch *const dispatch)
{
	size_t				size;
	char				*new;

	if (TOKEN.type & TOK_GLOB && !(TOKEN.type & TOK_DOLLAR))
		return (perfom_globing(dispatch));
	size = 0;
	new = TOKEN.src;
	while (*new)
	{
		if (g_perfoms[(int)*new].index)
			size += g_perfoms[(int)*new].func_len(dispatch, &new);
		else
		{
			size++;
			new++;
		}
	}
	perfom_common_replace(dispatch, size);
}

void					foreground_perfom(t_dispatch *const dispatch)
{
	while (TOKENSRC)
	{
		if (TOKEN.type & TOK_COMMON && TOKEN.type & TOK_REQ)
		{
			if (TOKEN.type & TOK_EQUAL)
			{
				SUPER(dispatch)->var.append(dispatch, TOKENSRC);
				ktoken(dispatch->foreground.tokens, FINDEX, 1);
				continue ;
			}
			perfom_common(dispatch);
		}
		else if (TOKEN.type & TOK_QUOTES)
		{
			if (TOKEN.type & TOK_Q && (TOKEN.type |= TOK_NEEDP))
			{
				perfom_common(dispatch);
				TOKEN.type = TOK_COMMON;
			}
			else if (TOKEN.type & TOK_QF)
				TOKEN.type = TOK_COMMON;
		}
		dispatch->foreground.index++;
	}
	dispatch->foreground.index = 0;
}
