/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collection_append.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 09:45:59 by afeuerst          #+#    #+#             */
/*   Updated: 2017/10/18 16:46:42 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void			collection_append_cmd(t_dispatch *const dispatch, t_cmd *cmd)
{
	t_cmd		*c;
	t_task		*l;

	if (!dispatch->foreground.collection.task)
		return ;
	l = dispatch->foreground.collection.task;
	while (l->next)
		l = l->next;
	if (!l->cmd)
	{
		l->cmd = cmd;
		dispatch->foreground.collection.ccmd = cmd;
	}
	else
	{
		c = l->cmd;
		while (c->next)
			c = c->next;
		c->next = cmd;
		dispatch->foreground.collection.ccmd = cmd;
	}
}

void			collection_append(t_dispatch *const dispatch,
		t_task *const task)
{
	t_task		*add;

	if (!dispatch->foreground.collection.task)
	{
		dispatch->foreground.collection.task = task;
		dispatch->foreground.collection.ctask = task;
	}
	else
	{
		add = dispatch->foreground.collection.task;
		while (add->next)
			add = add->next;
		add->next = task;
		dispatch->foreground.collection.ctask = task;
	}
}
