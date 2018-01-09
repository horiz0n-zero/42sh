/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_readcolor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 10:37:16 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 16:06:06 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const uint64_t				g_properties_offset[PROPERTIES_COUNT] =
{
	offsetof(t_dispatch, display.properties.location_color),
	offsetof(t_dispatch, display.properties.separator_string),
	offsetof(t_dispatch, display.properties.separator_color),
	offsetof(t_dispatch, display.properties.prompt_string),
	offsetof(t_dispatch, display.properties.prompt_color),
	offsetof(t_dispatch, display.properties.text_color),
	offsetof(t_dispatch, display.properties.builtins_color)
};

static void							readcolor(t_dispatch *const dispatch,
		const char *const ptr)
{
	const t_color_section *const	sections = CHOUETTE;
	int								index;
	char							**target;
	const char						*data;

	index = 0;
	while (index < PROPERTIES_COUNT)
	{
		target = (void*)(g_properties_offset[index] + (char*)dispatch);
		data = sections[index].offset + ptr;
		if (*target)
			free(*target);
		if (data)
			*target = SUPER(dispatch)->string.ncopy(data, sections[index].len);
		index++;
	}
}

void								display_readcolor(
		t_dispatch *const dispatch)
{
	void							*ptr;
	struct stat						chat;
	const t_color_header			*header;

	if (fstat(dispatch->display.colors, &chat))
		return ;
	if ((uint64_t)chat.st_size < sizeof(t_color_header))
		return ;
	if (!(ptr = malloc((size_t)chat.st_size)))
		return ;
	read(dispatch->display.colors, ptr, (size_t)chat.st_size);
	header = ptr;
	if (header->magic != MAGIC_COLOR || header->size != (uint64_t)chat.st_size)
		return (free(ptr));
	readcolor(dispatch, ptr);
	free(ptr);
}
