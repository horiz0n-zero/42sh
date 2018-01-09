/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 10:49:19 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 15:59:04 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static int				get_hash(t_dispatch *const dispatch)
{
	void				*e;

	e = SUPER(dispatch)->foreground.builtins.get(dispatch, TOKENSRC);
	if (e)
	{
		dispatch->foreground.collection.ccmd->type = CMD_BUILT;
		dispatch->foreground.collection.ccmd->func = e;
		dispatch->foreground.collection.ccmd->argv = (void*)TOKENSRC;
		dispatch->foreground.index++;
		return (0);
	}
	e = SUPER(dispatch)->foreground.binaries.get(dispatch, TOKENSRC);
	if (e)
	{
		dispatch->foreground.collection.ccmd->type = CMD_OK;
		dispatch->foreground.collection.ccmd->argv = e;
		ktoken(dispatch->foreground.tokens, dispatch->foreground.index, true);
		return (0);
	}
	return (1);
}

void					foreground_get_exec(t_dispatch *const dispatch)
{
	struct stat			chat;

	if (!dispatch->foreground.collection.ccmd)
		return ;
	if (!get_hash(dispatch))
		return ;
	else if (!stat(TOKENSRC, &chat) && chat.st_mode & S_IFREG && chat.st_mode &
			S_IXUSR)
	{
		dispatch->foreground.collection.ccmd->type = CMD_OK;
		dispatch->foreground.collection.ccmd->argv = (void*)TOKENSRC;
		dispatch->foreground.index++;
	}
	else
	{
		ft_vasprintf(&dispatch->foreground.error, UNK_COMMAND, TOKENSRC);
		dispatch->foreground.error_required_free = 1;
		ktoken(dispatch->foreground.tokens, dispatch->foreground.index, true);
	}
}
