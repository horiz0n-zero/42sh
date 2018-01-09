/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 11:38:27 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/02 15:59:24 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const int	g_reaction[256] =
{
	[' ']= 1,
	['\n']= 1,
	['\t']= 1
};

static size_t		split_count(const char *src)
{
	size_t			count;

	count = 1;
	while (*src)
	{
		while (*src && g_reaction[(int)*src])
			src++;
		if (*src)
		{
			count++;
			while (*src && !g_reaction[(int)*src])
				src++;
		}
	}
	return (count);
}

static void			*split_copy(const char *src)
{
	char			*new;
	size_t			size;

	size = 0;
	while (src[size] && !g_reaction[(int)src[size]])
		size++;
	if (!(new = malloc(size + 1)))
		malloc_exit();
	while (*src && !g_reaction[(int)*src])
		*new++ = *src++;
	*new = 0;
	return (new - size);
}

void				*string_split(const char *src)
{
	char			**new;
	const size_t	count = split_count(src);

	if (!(new = malloc(sizeof(char*) * count)))
		malloc_exit();
	while (*src)
	{
		while (g_reaction[(int)*src])
			src++;
		if (*src)
		{
			*new++ = split_copy(src);
			while (*src && !g_reaction[(int)*src])
				src++;
		}
	}
	*new = NULL;
	return (new - count + 1);
}
