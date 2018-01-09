/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_autoselect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstoian <kstoian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:30:56 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/05 14:19:08 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static int			world_matching(register const char *world,
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

static size_t		search_world_count(const char *const world)
{
	DIR *const			dir = opendir(".");
	struct dirent		*tmp;
	size_t				count;

	count = 0;
	if (!dir)
		return (0);
	while ((tmp = readdir(dir)))
	{
		if (*tmp->d_name == '.' ||
				!world_matching(world, tmp->d_name))
			continue ;
		count++;
	}
	closedir(dir);
	return (count);
}

static inline void	autopushing(t_dispatch *const dispatch,
		const char *const backworld)
{
	size_t			len;

	len = ft_strlen(backworld);
	dispatch->display.select.array->selected = true;
	while (len--)
		SUPER(dispatch)->display.remove(dispatch);
	SUPER(dispatch)->display.selected(dispatch);
}

void				display_autoselect(t_dispatch *const dispatch,
		char *const backworld)
{
	const size_t	count = search_world_count(backworld);
	size_t			len;

	if (!count)
		return ((void)write(STDOUT_FILENO, CAPS(BL).s, CAPS(BL).l));
	dispatch->display.select.count = count;
	dispatch->display.select.array = malloc(sizeof(t_select) * count);
	search_world_append(backworld, dispatch->display.select.array,
			&dispatch->display.select, dispatch);
	if (count == 1)
		return (autopushing(dispatch, backworld));
	dispatch->display.select.coz = !(dispatch->display.co <
							dispatch->display.select.len) ?
				dispatch->display.co / dispatch->display.select.len : 1;
	len = ft_strlen(backworld);
	while (len--)
		SUPER(dispatch)->display.remove(dispatch);
	SUPER(dispatch)->display.select(dispatch);
}
