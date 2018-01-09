/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor_hashablebin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 11:54:57 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/22 16:50:27 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void			hashbin_dir_append(const char *path,
		t_dispatch *const dispatch)
{
	struct dirent	*tmp;
	DIR *const		purpledir = opendir(path);
	struct stat		chat;
	char			*join;

	if (purpledir)
	{
		while ((tmp = readdir(purpledir)))
		{
			if (tmp->d_name[0] == '.')
				continue ;
			join = ft_strcjoin(path, tmp->d_name, '/');
			stat(join, &chat);
			if (chat.st_mode & S_IFREG && chat.st_mode & S_IXUSR)
			{
				SUPER(dispatch)->foreground.binaries.append(dispatch,
						SUPER(dispatch)->string.copy(tmp->d_name),
						join);
			}
			else
				free(join);
		}
		closedir(purpledir);
	}
}

static void			hashbin_append(t_dispatch *const dispatch)
{
	char			*path;
	char			*ptr;
	int				is_doublepoint;

	path = SUPER(dispatch)->env.get(dispatch, "PATH");
	if (!path)
		return ;
	ptr = path;
	while (*ptr)
	{
		while (*ptr && *ptr != ':')
			ptr++;
		if (*ptr == ':')
			is_doublepoint = true;
		else
			is_doublepoint = false;
		*ptr = 0;
		hashbin_dir_append(path, dispatch);
		if (is_doublepoint)
			*ptr++ = ':';
		else
			break ;
		path = ptr;
	}
}

static size_t		hashbin_dir_count(const char *path)
{
	struct dirent	*tmp;
	DIR *const		purpledir = opendir(path);
	size_t			count;
	struct stat		chat;

	count = 0;
	if (purpledir)
	{
		while ((tmp = readdir(purpledir)))
		{
			if (tmp->d_name[0] == '.')
				continue ;
			stat(ft_stccjoin(path, tmp->d_name, '/'), &chat);
			if (chat.st_mode & S_IFREG && chat.st_mode & S_IXUSR)
				count++;
		}
		closedir(purpledir);
	}
	return (count);
}

static size_t		hashbin_count(t_dispatch *const dispatch)
{
	size_t			count;
	char			*path;
	char			*ptr;
	int				is_doublepoint;

	count = 1;
	path = SUPER(dispatch)->env.get(dispatch, "PATH");
	if (!path)
		return (count);
	ptr = path;
	while (*ptr)
	{
		while (*ptr && *ptr != ':')
			ptr++;
		is_doublepoint = *ptr == ':' ? true : false;
		*ptr = 0;
		count += hashbin_dir_count(path);
		if (is_doublepoint)
			*ptr++ = ':';
		else
			break ;
		path = ptr;
	}
	return (count);
}

void				ctor_hashablebin(t_dispatch *const dispatch)
{
	dispatch->foreground.binaries.size = hashbin_count(dispatch);
	dispatch->foreground.binaries.packets =
		malloc(sizeof(t_hashpacket) * dispatch->foreground.binaries.size);
	if (!dispatch->foreground.binaries.packets)
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	ft_memset((void*)dispatch->foreground.binaries.packets, \
			dispatch->foreground.binaries.size * sizeof(t_hashpacket));
	hashbin_append(dispatch);
}
