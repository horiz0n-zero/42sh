/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:11:06 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 16:58:17 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const t_redinfo	g_infos[] =
{
	[TYPE_R] = {O_WRONLY | O_CREAT | O_TRUNC, R_PATH, STDOUT_FILENO, -1, NULL},
	[TYPE_RR] = {O_WRONLY | O_CREAT | O_APPEND, R_PATH, STDOUT_FILENO, -1,
		NULL},
	[TYPE_L] = {O_RDONLY, R_PATH | 2, STDIN_FILENO, -1, NULL},
	[TYPE_LL] = {O_RDONLY, R_PATH, STDIN_FILENO, -1, red_heredoc},
	[TYPE_LLL] = {O_RDONLY, R_PATH, STDIN_FILENO, -1, red_herestring},
	[TYPE_AR] = {-1, 0, STDIN_FILENO, STDERR_FILENO, red_and},
	[TYPE_LA] = {-1, 0, STDOUT_FILENO, STDERR_FILENO, red_and},
	[TYPE_IO] = {O_RDWR | O_APPEND | O_CREAT, R_PATH | 2, STDIN_FILENO,
		STDOUT_FILENO, NULL},
	[TYPE_RA] = {-1, 0, STDIN_FILENO, STDERR_FILENO, red_and},
	[TYPE_AL] = {-1, 0, STDOUT_FILENO, STDERR_FILENO, red_and}
};

static inline void		redirections_args(t_dispatch *const dispatch,
		t_red *const red, const int i)
{
	struct stat			chat;

	if (g_infos[i].setting & R_PATH)
	{
		if (TOKENSRC && TOKEN.type & (TOK_COMMON | TOK_QUOTES))
			red->file = SUPER(dispatch)->string.copy(TOKENSRC);
		else
		{
			if (TOKENSRC)
				ft_vasprintf(&dispatch->foreground.error,
					"Bad redirection arguments %s.\n", TOKENSRC);
			else
				ft_vasprintf(&dispatch->foreground.error,
					"This type of redirection required a path.\n");
			return ((void)(dispatch->foreground.error_required_free = true));
		}
		if (g_infos[i].setting & 2 && stat(red->file, &chat))
		{
			ft_vasprintf(&ERROR, "Bad file %s.\n", red->file);
			dispatch->foreground.error_required_free = true;
		}
		ktoken(dispatch->foreground.tokens, dispatch->foreground.index, true);
	}
	if (g_infos[i].func)
		g_infos[i].func(dispatch, red);
}

static inline void		redirections(t_dispatch *const dispatch,
		t_red *const red)
{
	int					i;

	if (*TOKENSRC >= '0' && *TOKENSRC <= '9')
	{
		i = 0;
		red->x = 0;
		while (TOKENSRC[i] >= '0' && TOKENSRC[i] <= '9')
			red->x = red->x * 10 + (TOKENSRC[i++] - '0');
		if (red->x > 2)
			red->x = -1;
		ktoken(dispatch->foreground.tokens, dispatch->foreground.index, true);
	}
	if (!(i = isoftype(TOKENSRC)))
	{
		ft_vasprintf(&dispatch->foreground.error, BAD_OPERATOR, TOKENSRC);
		return ((void)(dispatch->foreground.error_required_free = true));
	}
	ktoken(dispatch->foreground.tokens, dispatch->foreground.index, true);
	red->mode = g_infos[i].mode;
	red->in = g_infos[i].in;
	red->out = g_infos[i].out;
	redirections_args(dispatch, red, i);
}

void					foreground_task_redirections(t_dispatch *const dispatch)
{
	t_red				*ptr;

	if (TOKEN.type & TOK_RED || (*TOKENSRC >= '0' && *TOKENSRC <= '9' &&
			TOKENS(dispatch->foreground.index + 1).src &&
			TOKENS(dispatch->foreground.index + 1).type & TOK_RED))
	{
		if (dispatch->foreground.collection.ctask->red)
		{
			ptr = dispatch->foreground.collection.ctask->red;
			while (ptr && ptr->next)
				ptr = ptr->next;
			ptr->next = new_red();
			ptr = ptr->next;
		}
		else
		{
			dispatch->foreground.collection.ctask->red = new_red();
			ptr = dispatch->foreground.collection.ctask->red;
		}
	}
	else
		return ;
	redirections(dispatch, ptr);
	if (TOKENSRC && TOKEN.type & TOK_RED && isoftype(TOKENSRC))
		foreground_redirections(dispatch);
}
