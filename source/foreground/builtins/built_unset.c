/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:43:32 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/03 15:50:06 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void		kpush_unset(t_dispatch *const dispatch, const size_t index)
{
	size_t		i;

	i = index;
	free(dispatch->var.local[index].key);
	dispatch->var.count--;
	while (i < dispatch->var.count)
	{
		dispatch->var.local[i].key = dispatch->var.local[i + 1].key;
		dispatch->var.local[i].value = dispatch->var.local[i + 1].value;
		i++;
	}
}

static void		will_unset(t_dispatch *const dispatch, const char *const key)
{
	size_t		index;

	index = 0;
	while (index < dispatch->var.count)
	{
		if (!ft_strcmp(key, dispatch->var.local[index].key))
		{
			if (environ_get(dispatch, key))
				environ_remove(dispatch, key);
			return (kpush_unset(dispatch, index));
		}
		index++;
	}
}

int				built_unset(t_dispatch *const dispatch, char **argv)
{
	if (*++argv)
	{
		while (*argv)
		{
			will_unset(dispatch, *argv++);
		}
	}
	else
		ft_printf("%sunset: not enough arguments\33[37m\n",
				dispatch->display.properties.builtins_color);
	return (0);
}
