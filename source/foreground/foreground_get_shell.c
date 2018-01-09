/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_get_shell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 10:36:42 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 16:25:26 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const int			g_typecor[256] =
{
	[TYPE_AND] = TASKI_AND,
	[TYPE_ANDAND] = TASKI_ANDAND,
	[TYPE_OR] = TASKI_OR,
	[TYPE_OROR] = TASKI_OROR,
	[TYPE_COMMA] = TASKI_COMMA
};

static void					foreground_shell_argv(t_dispatch *const dispatch)
{
	int						type;

	while (TOKENSRC)
	{
		SUPER(dispatch)->foreground.task_redirections(dispatch);
		if (!TOKENSRC || dispatch->foreground.error)
			break ;
		if (TOKEN.type & TOK_RED)
			continue ;
		else
			break ;
	}
	if (TOKENSRC && TOKEN.type & (TOK_AND | TOK_OR | TOK_COMMA))
	{
		type = isoftype(TOKENSRC);
		if (!type || !(type = g_typecor[type]))
		{
			ft_vasprintf(&dispatch->foreground.error, BAD_OPERATOR, TOKENSRC);
			dispatch->foreground.error_required_free = true;
		}
		else
			ktoken(dispatch->foreground.tokens, dispatch->foreground.index, 1);
		dispatch->foreground.collection.ctask->type |= type;
	}
}

static inline void			get_shell_work(t_dispatch *const dispatch)
{
	dispatch->display.len = ft_strlen(TOKENSRC);
	while (dispatch->display.buffer_size < dispatch->display.len)
		dispatch->display.buffer_size *= 2;
	if (!(dispatch->display.buffer = malloc(dispatch->display.buffer_size + 1)))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size + 1);
	SUPER(dispatch)->memory.move(dispatch->display.buffer,
			TOKENSRC, dispatch->display.len);
	ktoken(dispatch->foreground.tokens, dispatch->foreground.index, true);
	dispatch->foreground.index = 0;
	dispatch->foreground.need_task = false;
	dispatch->foreground.tokens = NULL;
	SUPER(dispatch)->foreground.get(dispatch);
	dispatch->foreground.collection.ctask->tokens = dispatch->foreground.tokens;
}

void						foreground_get_shell(t_dispatch *const dispatch)
{
	t_token *const			tokens = dispatch->foreground.tokens;
	const int				index = dispatch->foreground.index;
	char *const				buffer = dispatch->display.buffer;
	const size_t			buffer_size = dispatch->display.buffer_size;
	const size_t			len = dispatch->display.len;

	get_shell_work(dispatch);
	free(dispatch->display.buffer);
	dispatch->foreground.tokens = tokens;
	dispatch->foreground.index = index;
	foreground_shell_argv(dispatch);
	dispatch->display.len = len;
	dispatch->display.buffer = buffer;
	dispatch->display.buffer_size = buffer_size;
	dispatch->foreground.need_task = true;
}
