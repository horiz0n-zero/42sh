/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_writecolor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 10:36:50 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/02 15:17:59 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const uint64_t		g_properties_offset[PROPERTIES_COUNT] =
{
	offsetof(t_dispatch, display.properties.location_color),
	offsetof(t_dispatch, display.properties.separator_string),
	offsetof(t_dispatch, display.properties.separator_color),
	offsetof(t_dispatch, display.properties.prompt_string),
	offsetof(t_dispatch, display.properties.prompt_color),
	offsetof(t_dispatch, display.properties.text_color),
	offsetof(t_dispatch, display.properties.builtins_color)
};

static void					writecolor(t_dispatch *const dispatch,
		const t_color_header *const header,
		const t_color_section *const sections)
{
	int						fd;
	char					*src;
	int						index;
	const char				**ptr;

	close(dispatch->display.colors);
	src = ft_stcjoin(dispatch->base, "_colors");
	fd = open(src, O_CREAT | O_TRUNC | O_WRONLY | O_APPEND);
	if (fd == -1)
		return ;
	write(fd, header, sizeof(t_color_header));
	write(fd, sections, sizeof(t_color_section) * PROPERTIES_COUNT);
	index = 0;
	while (index < PROPERTIES_COUNT)
	{
		ptr = (const char**)(void*)(g_properties_offset[index] +
				(char*)dispatch);
		write(fd, *ptr, (size_t)sections[index].len);
		index++;
	}
	close(fd);
}

void						display_writecolor(t_dispatch *const dispatch)
{
	t_color_header			header;
	t_color_section			sections[PROPERTIES_COUNT];
	int						index;
	uint64_t				offset;
	const char				**ptr;

	if (!dispatch->base)
		return ;
	header.magic = MAGIC_COLOR;
	index = 0;
	offset = sizeof(t_color_header) + sizeof(t_color_section) *
		PROPERTIES_COUNT;
	while (index < PROPERTIES_COUNT)
	{
		sections[index].offset = offset;
		ptr = (const char**)(void*)(g_properties_offset[index] +
				(char*)dispatch);
		sections[index].len = (uint64_t)ft_strlen(*ptr);
		offset += sections[index].len;
		index++;
	}
	header.size = offset;
	writecolor(dispatch, &header, sections);
}
