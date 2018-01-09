/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ismatching.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 10:18:12 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/08 10:40:28 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				glob_append(const char *const src, t_array *const a)
{
	void			*new;

	if (a->count + 2 >= a->size)
	{
		a->size *= 2;
		new = malloc(sizeof(char*) * a->size);
		if (!new)
			malloc_exit();
		memory_move(new, (const void*)a->array, a->count * sizeof(char*));
		free(a->array);
		a->array = new;
	}
	a->array[a->count++] = string_copy(src);
	a->array[a->count] = NULL;
}

static int			glob_square_brackets(const char *glob, const char c)
{
	int				i;
	int				j;
	char			*inside;

	i = 0;
	j = 0;
	inside = string_copy(glob);
	while (inside[i] && inside[i] != ']')
		i++;
	if (inside[i] == '\0')
		return (false);
	while (j < i)
	{
		if (j > 0 && inside[j] == '-' && inside[j + 1] && c >= inside[j - 1] &&
				c <= inside[j + 1])
			break ;
		else if (c == inside[j])
			break ;
		j++;
	}
	free(inside);
	return (j < i ? i : false);
}

static inline int	is_squarebracket(register const char *glob,
		register const char *name)
{
	while (*glob && *glob != ']')
		glob++;
	if (*glob == ']')
		glob++;
	name++;
	return (ismatching(glob, name));
}

int					ismatching(register const char *glob,
		register const char *name)
{
	while (*glob && *name)
	{
		if (*glob == '[' && glob_square_brackets(glob + 1, *name))
			return (is_squarebracket(glob, name));
		else if (*glob++ == '*')
		{
			if (!*glob)
				return (true);
			while (*name)
			{
				if (ismatching(glob, name) == true)
					return (true);
				name++;
			}
			return (false);
		}
		else if (*glob == '?' || *glob == *name)
		{
			name++;
			glob++;
		}
		else
			return (false);
	}
	return (!name || (!*name) ? true : false);
}
