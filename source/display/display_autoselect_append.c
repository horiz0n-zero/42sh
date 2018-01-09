/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_autoselect_append.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstoian <kstoian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 17:22:29 by kstoian           #+#    #+#             */
/*   Updated: 2018/01/05 14:22:27 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void	setup_select_wappend(t_select *const select, struct dirent *tmp)
{
	select->name = string_copy(tmp->d_name);
	select->len = ft_strlen(tmp->d_name);
}

static int	world_matching(register const char *world,
		register const char *src)
{
	while (*world)
	{
		if (!*src || *world != *src)
			return (false);
		world++;
		src++;
	}
	return (true);
}

void		search_world_append(const char *const world,
		t_select *select, t_selection *const selection,
		t_dispatch *const dispatch)
{
	DIR *const		dir = opendir(".");
	struct dirent	*tmp;
	struct stat		chat;
	size_t			len;

	len = 0;
	if (!dir)
		return ;
	while ((tmp = readdir(dir)))
	{
		if (*tmp->d_name == '.' || !world_matching(world, tmp->d_name))
			continue ;
		setup_select_wappend(select, tmp);
		if (select->len >= len)
			len = select->len + 1;
		select->bg = "";
		if (!stat(tmp->d_name, &chat) && S_ISDIR(chat.st_mode))
			select->fg = dispatch->display.properties.location_color;
		else
			select->fg = dispatch->display.properties.text_color;
		select->selected = false;
		select->cursor = false;
		select++;
	}
	(selection->len = len) && !(closedir(dir));
}
