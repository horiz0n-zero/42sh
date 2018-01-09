/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 09:55:41 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/03 14:54:19 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void		extra_task(t_dispatch *const dispatch)
{
	if (TOKEN.type & TOK_PRE)
	{
		SUPER(dispatch)->foreground.collection.append(dispatch, new_task());
		SUPER(dispatch)->foreground.get_subshell(dispatch);
	}
	else if (TOKEN.type & TOK_SKULL)
	{
		SUPER(dispatch)->foreground.collection.append(dispatch, new_task());
		SUPER(dispatch)->foreground.get_shell(dispatch);
	}
	else if (TOKEN.type & TOK_INI)
	{
		SUPER(dispatch)->foreground.get_inibit(dispatch, NULL);
	}
}

static void				get_args(t_dispatch *const dispatch)
{
	if (TOKEN.type & (TOK_SKULL | TOK_PRE | TOK_INI))
		return (extra_task(dispatch));
	else
	{
		if (dispatch->foreground.need_task ||
				!dispatch->foreground.collection.task)
		{
			dispatch->foreground.need_task = false;
			SUPER(dispatch)->foreground.collection.append(dispatch, new_task());
		}
		SUPER(dispatch)->foreground.collection.append_cmd(dispatch, new_cmd());
	}
	if (TOKEN.type & TOK_COMMON)
		SUPER(dispatch)->foreground.get_exec(dispatch);
	SUPER(dispatch)->foreground.get_argv(dispatch, 0);
}

void					foreground_noget(t_dispatch *const dispatch)
{
	SUPER(dispatch)->foreground.history(dispatch);
	if (!dispatch->foreground.tokens)
		return ;
	while (TOKENSRC)
	{
		while (TOKENSRC && TOKEN.type & TOK_SEP && !(TOKEN.type & TOK_RED))
		{
			if (isoftype(TOKENSRC) != TYPE_COMMA)
			{
				ft_vasprintf(&ERROR, BAD_OPERATOR, TOKENSRC);
				dispatch->foreground.error_required_free = 1;
				return ;
			}
			ktoken(dispatch->foreground.tokens, dispatch->foreground.index, 1);
		}
		if (TOKENSRC)
			get_args(dispatch);
		if (dispatch->foreground.error)
			break ;
	}
}

void					foreground_get(t_dispatch *const dispatch)
{
	SUPER(dispatch)->foreground.history(dispatch);
	dispatch->foreground.tokens = SUPER(dispatch)->string.toksplit(dispatch);
	if (!dispatch->foreground.tokens)
		return ;
	SUPER(dispatch)->foreground.perfom(dispatch);
	while (TOKENSRC)
	{
		while (TOKENSRC && TOKEN.type & TOK_SEP && !(TOKEN.type & TOK_RED))
		{
			if (isoftype(TOKENSRC) != TYPE_COMMA)
			{
				ft_vasprintf(&ERROR, BAD_OPERATOR, TOKENSRC);
				dispatch->foreground.error_required_free = 1;
				return ;
			}
			ktoken(dispatch->foreground.tokens, dispatch->foreground.index, 1);
		}
		if (TOKENSRC)
			get_args(dispatch);
		if (dispatch->foreground.error)
			break ;
	}
}
