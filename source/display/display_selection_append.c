/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_selection_append.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstoian <kstoian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 17:14:04 by kstoian           #+#    #+#             */
/*   Updated: 2018/01/04 17:31:33 by kstoian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void		setup_select(t_select *const select, struct dirent *tmp)
{
	select->name = string_copy(tmp->d_name);
	select->selected = false;
	select->cursor = false;
	select->bg = "";
}

void			open_append(const char *const path, t_select *select,
		t_selection *const selection, t_dispatch *const dispatch)
{
	DIR *const		dir = opendir(path);
	struct dirent	*tmp;
	struct stat		chat;
	size_t			len;

	len = 0;
	if (!dir)
		return ;
	while ((tmp = readdir(dir)))
	{
		if (*tmp->d_name == '.')
			continue ;
		setup_select(select, tmp);
		if (!stat(ft_stccjoin(path, select->name, '/'), &chat) &&
				S_ISDIR(chat.st_mode))
			select->fg = dispatch->display.properties.location_color;
		else
			select->fg = dispatch->display.properties.text_color;
		select->len = ft_strlen(select->name);
		if (select->len >= len)
			len = select->len + 1;
		select++;
	}
	selection->len = len;
	closedir(dir);
}
