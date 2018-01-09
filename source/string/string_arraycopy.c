/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_arraycopy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 09:12:44 by afeuerst          #+#    #+#             */
/*   Updated: 2017/10/30 09:20:38 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static size_t		strings_count(const char **src)
{
	size_t			count;

	count = 0;
	while (*src++)
		count++;
	return (count);
}

static inline void	*strings_copy(const char *src)
{
	size_t			size;
	char			*new;

	size = 0;
	while (src[size])
		size++;
	if (!(new = malloc(size + 1)))
		malloc_exit();
	while (*src)
		*new++ = *src++;
	*new = 0;
	return (new - size);
}

void				*string_arraycopy(const char **src)
{
	const size_t	count = strings_count(src);
	char			**new;

	if (!(new = malloc(sizeof(char*) * (count + 1))))
		malloc_exit();
	while (*src)
		*new++ = strings_copy(*src++);
	*new = 0;
	return (new - count);
}
