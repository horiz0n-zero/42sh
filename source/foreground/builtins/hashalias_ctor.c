/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashalias_ctor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 13:56:56 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/05 13:28:21 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void			alias_append(t_dispatch *const dispatch, char *content)
{
	char			**split;
	char			*ptr;
	char			*args;

	while (*content)
	{
		if (*content == '>' && *++content == ' ')
		{
			ptr = ++content;
			while (*content && *content != ' ')
				content++;
			*content++ = 0;
			args = content;
			while (*content && *content != '\n')
				content++;
			*content++ = 0;
			split = SUPER(dispatch)->string.split(args);
			SUPER(dispatch)->foreground.alias.append(dispatch,
					SUPER(dispatch)->string.copy(ptr), split);
		}
		else
			content++;
	}
}

static void			alias_count(t_dispatch *const dispatch, char *content)
{
	size_t			count;

	count = 0;
	if (!*content)
	{
		dispatch->foreground.alias.size = 10;
		return ;
	}
	while (*content)
	{
		if (*content == '>' && *++content == ' ')
		{
			count++;
			while (*content && *content != '\n')
				content++;
		}
		else
			content++;
		if (*content == '\n')
			content++;
	}
	dispatch->foreground.alias.size = count;
}

void				ctor_hashalias(t_dispatch *const dispatch)
{
	char			*file;
	struct stat		chat;

	fstat(dispatch->foreground.aliasfile, &chat);
	if (!(file = malloc((size_t)chat.st_size + 1)))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	read(dispatch->foreground.aliasfile, file, (size_t)chat.st_size);
	*(file + chat.st_size) = 0;
	alias_count(dispatch, file);
	dispatch->foreground.alias.packets = malloc(sizeof(t_hashpacket) *
			dispatch->foreground.alias.size);
	if (!dispatch->foreground.alias.packets)
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	ft_memset((char*)dispatch->foreground.alias.packets, sizeof(t_hashpacket) *
			dispatch->foreground.alias.size);
	alias_append(dispatch, file);
	free(file);
}
