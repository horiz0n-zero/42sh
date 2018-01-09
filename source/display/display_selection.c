/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_selection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstoian <kstoian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 11:32:02 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/04 17:13:50 by kstoian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void			*selection_backworld(t_dispatch *const dispatch)
{
	static char		buffy[1024];
	char			*ptr;
	int				index;

	if ((index = (int)dispatch->display.index - 1) >= 0)
	{
		ptr = buffy;
		if (BUFFER(index) != ' ')
		{
			while (index >= 0 && BUFFER(index) != ' ')
				*ptr++ = BUFFER(index--);
			*ptr = 0;
			SUPER(dispatch)->string.swap(buffy);
		}
		else
			return (".");
		return (buffy);
	}
	return (".");
}

static size_t		open_count(const char *const path)
{
	DIR *const		dir = opendir(path);
	struct dirent	*tmp;
	size_t			count;

	count = 0;
	if (!dir)
		return (count);
	while ((tmp = readdir(dir)))
	{
		if (*tmp->d_name == '.')
			continue ;
		count++;
	}
	closedir(dir);
	return (count);
}

static inline void	add_slash(t_dispatch *const dispatch, char *back)
{
	if (*back == '.' && !*(back + 1))
		return ;
	dispatch->display.select.app = true;
	dispatch->display.select.ref = back;
	dispatch->display.select.ref_len = ft_strlen(back);
	if (*back == '/' && !*(back + 1))
		return ;
	while (*back)
		back++;
	if (*--back != '/')
	{
		SUPER(dispatch)->display.append('/', dispatch);
		*++back = '/';
		*++back = 0;
		dispatch->display.select.ref_len++;
		dispatch->display.len++;
	}
}

void				display_selection(t_dispatch *const dispatch)
{
	char *const		backworld = selection_backworld(dispatch);
	struct stat		chat;
	size_t			size;

	if (stat(backworld, &chat))
		return (SUPER(dispatch)->display.autoselect(dispatch, backworld));
	else
	{
		if (S_ISDIR(chat.st_mode) && chat.st_mode & S_IRUSR)
		{
			if (!(size = open_count(backworld)))
				return ((void)write(STDOUT_FILENO, CAPS(BL).s, CAPS(BL).l));
			dispatch->display.select.array = malloc(sizeof(t_select) * size);
			dispatch->display.select.count = size;
			open_append(backworld, dispatch->display.select.array,
					&dispatch->display.select, dispatch);
			add_slash(dispatch, backworld);
			dispatch->display.select.coz = !(dispatch->display.co <
					dispatch->display.select.len) ?
				dispatch->display.co / dispatch->display.select.len : 1;
			SUPER(dispatch)->display.select(dispatch);
		}
		else
			return ((void)write(STDOUT_FILENO, CAPS(BL).s, CAPS(BL).l));
	}
}
