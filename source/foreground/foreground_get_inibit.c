/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_get_inibit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 10:34:25 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 15:57:36 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void			insert_result(t_dispatch *const dispatch, const char *name,
		t_token **const new, size_t i)
{
	struct stat		chat;
	char			*content;
	char			**split;
	const int		fd = open(name, O_RDONLY);

	stat(name, &chat);
	if (!(content = malloc((size_t)chat.st_size + 1)))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	read(fd, content, (size_t)chat.st_size);
	*(content + chat.st_size) = 0;
	split = SUPER(dispatch)->string.split(content);
	while (split[i])
		i++;
	if (!(*new = malloc(sizeof(t_token) * (i + 1))))
		malloc_exit();
	i = 0;
	while (split[i])
	{
		(*new)[i].src = split[i];
		(*new)[i++].type = TOK_COMMON;
	}
	(*new)[i].src = NULL;
	free(split);
	free(content);
	close(fd);
}

static void			execute_inibit(t_dispatch *const dispatch,
		t_token **const new)
{
	pid_t			pid;
	char			*name;
	int				fd;
	t_task			*task;

	name = SUPER(dispatch)->string.random(dispatch, 15, "/tmp/.42sh_");
	if (!(pid = fork()))
	{
		fd = open(name, O_CREAT | O_TRUNC | O_WRONLY,
				dispatch->foreground.red_mode);
		task = dispatch->foreground.collection.task;
		while (task && (task->stdout = fd))
			task = task->next;
		SUPER(dispatch)->foreground.execute(dispatch);
		SUPER(dispatch)->foreground.destroy(dispatch);
		exit(dispatch->foreground.status);
	}
	else
	{
		waitpid(pid, &dispatch->foreground.status, dispatch->foreground.wait);
		SUPER(dispatch)->foreground.destroy(dispatch);
		insert_result(dispatch, name, new, 0);
	}
}

static void			inibiter_norme(t_dispatch *const dispatch, const int f,
		t_token *const new)
{
	static void		*ctask = NULL;
	static void		*ccmd = NULL;
	static void		*task = NULL;

	if (f)
	{
		task = dispatch->foreground.collection.task;
		ctask = dispatch->foreground.collection.ctask;
		ccmd = dispatch->foreground.collection.ccmd;
	}
	else
	{
		dispatch->foreground.need_task = false;
		dispatch->foreground.collection.task = task;
		dispatch->foreground.collection.ctask = ctask;
		dispatch->foreground.collection.ccmd = ccmd;
		if (new)
		{
			tokensinsert(dispatch, new);
			free(new);
		}
	}
}

static void			inibiter_zero(t_dispatch *const dispatch)
{
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size + 1);
	SUPER(dispatch)->memory.move(dispatch->display.buffer,
			TOKENSRC, dispatch->display.len);
	ktoken(dispatch->foreground.tokens, dispatch->foreground.index, true);
	dispatch->foreground.index = 0;
	dispatch->foreground.tokens = NULL;
	dispatch->foreground.need_task = false;
	dispatch->foreground.collection.task = NULL;
	dispatch->foreground.collection.ctask = NULL;
	dispatch->foreground.collection.ccmd = NULL;
}

void				foreground_get_inibit(t_dispatch *const dispatch,
		t_token *new)
{
	t_token *const	tokens = dispatch->foreground.tokens;
	const int		index = dispatch->foreground.index;
	char *const		buffer = dispatch->display.buffer;
	const size_t	buffer_size = dispatch->display.buffer_size;
	const size_t	len = dispatch->display.len;

	inibiter_norme(dispatch, true, new);
	dispatch->display.len = ft_strlen(TOKENSRC);
	while (dispatch->display.buffer_size < dispatch->display.len)
		dispatch->display.buffer_size *= 2;
	if (!(dispatch->display.buffer = malloc(dispatch->display.buffer_size + 1)))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	inibiter_zero(dispatch);
	SUPER(dispatch)->foreground.get(dispatch);
	if (!dispatch->foreground.error)
		execute_inibit(dispatch, &new);
	free(dispatch->foreground.tokens);
	free(dispatch->display.buffer);
	dispatch->foreground.tokens = tokens;
	dispatch->foreground.index = index;
	dispatch->display.len = len;
	dispatch->display.buffer = buffer;
	dispatch->display.buffer_size = buffer_size;
	inibiter_norme(dispatch, false, new);
}
