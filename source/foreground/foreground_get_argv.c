/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:35:28 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/02 12:11:35 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void					add_separator(t_dispatch *const dispatch)
{
	int						type;

	type = isoftype(TOKENSRC);
	if (!type)
	{
		ft_vasprintf(&dispatch->foreground.error, BAD_OPERATOR, TOKENSRC);
		dispatch->foreground.error_required_free = true;
		return ;
	}
	else
	{
		dispatch->foreground.collection.ccmd->typeoff = type;
		ktoken(dispatch->foreground.tokens, dispatch->foreground.index, true);
	}
}

static void					add_argv(t_dispatch *const dispatch, size_t count,
							const int start)
{
	char					**new;

	dispatch->foreground.index = start;
	if (!(new = malloc(sizeof(char*) * (count + 2))))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	*new = (void*)dispatch->foreground.collection.ccmd->argv;
	dispatch->foreground.collection.ccmd->argv = new++;
	dispatch->foreground.collection.ccmd->isdone = true;
	while (count-- > 0)
	{
		*new++ = TOKENSRC;
		dispatch->foreground.index++;
	}
	*new = NULL;
	if (TOKENSRC && TOKEN.type & TOK_SEP)
		add_separator(dispatch);
}

void						foreground_get_argv(t_dispatch *const dispatch,
		size_t count)
{
	const int				start = dispatch->foreground.index;

	while (TOKENSRC)
	{
		SUPER(dispatch)->foreground.redirections(dispatch);
		if (!TOKENSRC || dispatch->foreground.error)
			break ;
		if (*TOKENSRC >= '0' && *TOKENSRC <= '9' &&
				TOKENS(dispatch->foreground.index + 1).src &&
				TOKENS(dispatch->foreground.index + 1).type & TOK_RED)
			continue ;
		if (TOKEN.type & TOK_COMMON)
			count++;
		else if (TOKEN.type & (TOK_SEP | TOK_PRE | TOK_SKULL))
			break ;
		else if (TOKEN.type & TOK_INI)
		{
			SUPER(dispatch)->foreground.get_inibit(dispatch, NULL);
			continue ;
		}
		else if (TOKEN.type & TOK_RED)
			continue ;
		dispatch->foreground.index++;
	}
	add_argv(dispatch, count, start);
}
