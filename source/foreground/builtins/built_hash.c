/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 11:19:01 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 14:32:23 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void			hash_show(t_dispatch *const dispatch)
{
	t_hashpacket	*pos;
	t_hashpacket	*ptr;
	size_t			i;

	i = 0;
	pos = dispatch->foreground.binaries.packets;
	while (i++ < dispatch->foreground.binaries.size)
	{
		ptr = pos++;
		while (ptr && ptr->src)
		{
			ft_printf("%s=%s\n", ptr->src, ptr->element);
			ptr = ptr->next;
		}
	}
}

int					built_hash(t_dispatch *const dispatch, char **argv)
{
	if (*++argv)
	{
		if (**argv == '-' && *(*argv + 1) == 'r' && !*(*argv + 2))
		{
			SUPER(dispatch)->foreground.binaries.dtor(dispatch);
			ft_printf("hash detroyed.\n");
			SUPER(dispatch)->foreground.binaries.ctor(dispatch);
			ft_printf("hash created.\n");
		}
		else
			ft_fprintf(STDERR_FILENO, "hash : usage : -r refresh\n");
	}
	else
		hash_show(dispatch);
	return (0);
}
