/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtor_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 10:43:14 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 14:15:09 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void					history_erase(t_dispatch *const dispatch,
		const t_history_header *const header,
		const t_history_section *const sections)
{
	uint64_t						index;

	index = 0;
	write(dispatch->history.guard, header, sizeof(t_history_header));
	write(dispatch->history.guard, sections,
			sizeof(t_history_section) * dispatch->history.count);
	while (index < dispatch->history.count)
	{
		write(dispatch->history.guard,
				dispatch->history.array[index].src,
				(uint64_t)sections[index].len);
		free(dispatch->history.array[index].src);
		index++;
	}
	free(dispatch->history.array);
}

static inline void					history_save(t_dispatch *const dispatch)
{
	t_history_header				header;
	t_history_section				sections[dispatch->history.count];
	uint64_t						index;
	uint64_t						offset;

	header.magic = MAGIC_HISTO;
	header.sections_count = (uint64_t)dispatch->history.count;
	offset = sizeof(t_history_header) +
		sizeof(t_history_section) * header.sections_count;
	index = 0;
	while (index < header.sections_count)
	{
		sections[index].offset = offset;
		sections[index].len = (uint64_t)
			ft_strlen(dispatch->history.array[index].src);
		sections[index].index = dispatch->history.array[index].index;
		offset += sections[index].len;
		index++;
	}
	header.file_size = offset;
	history_erase(dispatch, &header, sections);
}

void								dtor_history(t_dispatch *const dispatch)
{
	char							*src;

	if (dispatch->history.guard != -1)
	{
		close(dispatch->history.guard);
		src = SUPER(dispatch)->env.get(dispatch, "HOME");
		if (!src)
		{
			SUPER(dispatch)->env.guard(dispatch);
			src = SUPER(dispatch)->env.get(dispatch, "HOME");
		}
		src = ft_stcjoin(src, "/.42sh/_history");
		dispatch->history.guard = open(src,
				O_WRONLY | O_APPEND | O_TRUNC | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
		history_save(dispatch);
		close(dispatch->history.guard);
	}
}
