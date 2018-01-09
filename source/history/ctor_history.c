/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 10:42:43 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 15:44:16 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void					history_init(t_dispatch *const dispatch,
		const size_t size)
{
	dispatch->history.size = 2;
	while (dispatch->history.size < size)
		dispatch->history.size *= 2;
	dispatch->history.array = malloc(sizeof(t_history_node) *
			dispatch->history.size);
	dispatch->history.count = 0;
	dispatch->history.index = 0;
}

static void							history_read(t_dispatch *const dispatch,
		const uint64_t size, const void *const ptr)
{
	const t_history_header *const	header = ptr;
	const t_history_section *const	sections = ptr + sizeof(t_history_header);
	uint64_t						index;

	history_init(dispatch, (size_t)header->sections_count);
	if (header->magic != MAGIC_HISTO || header->file_size != size)
		return ;
	index = 0;
	while (index < header->sections_count)
	{
		dispatch->history.count++;
		dispatch->history.array[index].src =
			string_ncopy(ptr + sections[index].offset, sections[index].len);
		dispatch->history.array[index].index = sections[index].index;
		dispatch->history.array[index].len = sections[index].len;
		index++;
	}
	if (!index)
		dispatch->history.index = index;
	else
		dispatch->history.index = (size_t)index - 1;
}

void								ctor_history(t_dispatch *const dispatch)
{
	const char *const				home = ENVGET("HOME");
	char							*path;
	struct stat						chat;
	void							*ptr;

	if (home)
	{
		path = ft_stcjoin(home, "/.42sh/_history");
		dispatch->history.guard = open(path, O_CREAT | O_RDONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
		if (dispatch->history.guard < 0 ||
				fstat(dispatch->history.guard, &chat))
			return (history_init(dispatch, 0));
		if (!chat.st_size || (uint64_t)chat.st_size < sizeof(t_history_header))
			return (history_init(dispatch, 0));
		ptr = malloc((size_t)chat.st_size);
		read(dispatch->history.guard, ptr, (size_t)chat.st_size);
		history_read(dispatch, (uint64_t)chat.st_size, ptr);
		free(ptr);
	}
	else
	{
		dispatch->history.guard = -1;
		history_init(dispatch, 0);
	}
}
