/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_toksplit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 11:36:27 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/05 14:25:32 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const int	g_tokcor[256] =
{
	[' '] = 1,
	['\n'] = 1,
	['\t'] = 1,
	[';'] = 2,
	['|'] = 2,
	['&'] = 2,
	['<'] = 2,
	['>'] = 2,
	['{'] = '}',
	['('] = ')',
	['\"'] = '\"',
	['\''] = '\'',
	['`'] = '`'
};

static inline int	getok_common(register t_dispatch *const dispatch,
		register int i, t_token *const token)
{
	int				z;
	char			*new;

	z = 0;
	while (BUFFER(i + z) && !g_tokcor[(int)BUFFER(i + z)])
	{
		if (BUFFER(i + z) == '\\')
			z++;
		z++;
	}
	if (!(new = malloc((size_t)(z + 1))))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	token->src = new;
	while (BUFFER(i) && !g_tokcor[(int)BUFFER(i)])
	{
		if (BUFFER(i) == '\\')
			i++;
		*new++ = BUFFER(i++);
	}
	*new = 0;
	token->type = TOK_COMMON + toktype_common(token->src);
	return (i);
}

static inline int	getok_separator(register t_dispatch *const dispatch,
		register int i, t_token *const token)
{
	int				z;
	char			*new;

	z = 0;
	while (BUFFER(i + z) && g_tokcor[(int)BUFFER(i + z)] == 2)
		z++;
	if (!(new = malloc((size_t)(z + 3))))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	token->src = new;
	token->typeoff = 0;
	while (BUFFER(i) && g_tokcor[(int)BUFFER(i)] == 2)
		*new++ = BUFFER(i++);
	*new = 0;
	token->type = TOK_SEP | toktype_sep(token->src, z);
	return (i);
}

static inline int	getok_quotes(register t_dispatch *const dispatch,
		register int i, t_token *const token)
{
	int				z;
	char			*new;
	const char		raw = (char)g_tokcor[(int)BUFFER(i++)];

	z = 0;
	while (BUFFER(i + z) && BUFFER(i + z) != raw)
	{
		if (BUFFER(i + z) == '\\')
			z++;
		z++;
	}
	if (!(new = malloc((size_t)(z + 1))))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	token->src = new;
	token->typeoff = (int)raw;
	while (BUFFER(i) && BUFFER(i) != raw)
	{
		if (BUFFER(i) == '\\')
			i++;
		*new++ = BUFFER(i++);
	}
	*new = 0;
	token->type = TOK_QUOTES | toktype_quote(raw);
	return (++i);
}

t_token				*string_toksplit(register t_dispatch *const dispatch)
{
	const size_t	count = SUPER(dispatch)->string.toksplit_count(dispatch);
	t_token *const	ptr = malloc(sizeof(t_token) * count);
	register int	i;
	int				index;
	int				type;

	i = 0;
	index = 0;
	if (!count)
		return (force_stop(ptr));
	while (BUFFER(i))
	{
		while (BUFFER(i) && g_tokcor[(int)BUFFER(i)] == 1)
			i++;
		if (!BUFFER(i))
			break ;
		if (!(type = g_tokcor[(int)BUFFER(i)]))
			i = getok_common(dispatch, i, ptr + index++);
		else if (type == 2)
			i = getok_separator(dispatch, i, ptr + index++);
		else
			i = getok_quotes(dispatch, i, ptr + index++);
	}
	ptr[index].src = NULL;
	return (ptr);
}
