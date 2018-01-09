/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_globing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:54:09 by jeblonde          #+#    #+#             */
/*   Updated: 2018/01/03 15:44:29 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline int	globing_skip(char *const path, char *const glob,
		DIR *const dir, int *const index)
{
	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	if (!*glob || !dir)
	{
		free(path);
		if (dir)
			closedir(dir);
		return (true);
	}
	if (*glob == '*' && *(glob + 1) == '/')
		index[2] = true;
	while (glob[index[0]] && glob[index[0]] != '/')
		index[0]++;
	if (glob[index[0]] == '/')
	{
		while (glob[index[0]] == '/')
			glob[index[0]++] = 0;
		index[1] = true;
	}
	return (false);
}

static void			globing(char *const path, char *const glob,
		t_array *const a, char *buffy)
{
	struct dirent	*tmp;
	struct stat		chat;
	int				index[3];
	DIR *const		dir = opendir(path);

	if (globing_skip(path, glob, dir, index))
		return ;
	while ((tmp = readdir(dir)))
	{
		if (tmp->d_name[0] == '.')
			continue ;
		if (ismatching(glob, tmp->d_name))
		{
			if (*path == '/' && !*(path + 1))
				buffy = ft_stcjoin(path, tmp->d_name);
			else
				buffy = ft_stccjoin(path, tmp->d_name, '/');
			if (!index[2])
				glob_append(buffy, a);
			if (index[1] && !stat(buffy, &chat) && chat.st_mode & S_IFDIR)
				globing(string_copy(buffy), glob + index[0], a, NULL);
		}
	}
	free(path);
	closedir(dir);
}

static void			*glob_to_tokens(t_array *const a)
{
	t_token			*new;
	int				i;

	if (!(new = malloc(sizeof(t_token) * (a->count + 1))))
		malloc_exit();
	i = 0;
	while (a->array[i])
	{
		new[i].src = a->array[i];
		new[i].type = TOK_COMMON;
		new[i].typeoff = 0;
		i++;
	}
	new[i].src = NULL;
	free(a->array);
	return (new);
}

static char			*globing_directory(char *const src, size_t *n)
{
	size_t			i;
	char			*path;

	i = 0;
	*n = 0;
	while (src && src[i] && src[i] != '*' && src[i] != '?' && src[i] != '[')
		i++;
	while (i > 0 && src[i] != '/')
		i--;
	*n = i;
	if (i > 0)
	{
		path = string_copy(src);
		path[i] = '\0';
		*n = i + 1;
	}
	else if (i == 0 && src[i] == '/')
	{
		path = string_copy("/");
		*n = i + 1;
	}
	else
		path = string_copy(".");
	return (path);
}

void				*foreground_globing(char *const src, size_t *const n)
{
	t_array			a;
	size_t			i;
	char			*path;

	a.size = 16;
	a.count = 0;
	a.array = malloc(sizeof(void*) * 16);
	if (!a.array)
		malloc_exit();
	a.array[0] = NULL;
	path = globing_directory(src, &i);
	globing(path, src + i, &a, NULL);
	*n = a.count;
	return (glob_to_tokens(&a));
}
