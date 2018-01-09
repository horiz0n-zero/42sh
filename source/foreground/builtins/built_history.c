/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 15:13:54 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/11 11:55:37 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void		history_usage(t_dispatch *const dispatch)
{
	ft_printf("%shistory usage :\n",
			dispatch->display.properties.builtins_color);
	ft_printf("-c remove and clear history.\n");
	ft_printf("-d [index] remove only the indexed line.\n");
	ft_printf("-a read and load history file.\n");
	ft_printf("-w write current history to history file.\n\33[37m");
}

static int				history_option(t_dispatch *const dispatch, char **argv)
{
	while (*argv)
	{
		if (**argv == '-')
		{
			if (*(*argv + 1) == 'c')
				return (histo_c(dispatch));
			else if (*(*argv + 1) == 'd')
				return (histo_d(dispatch, argv));
			else if (*(*argv + 1) == 'a')
				return (histo_a(dispatch));
			else if (*(*argv + 1) == 'w')
				return (histo_w(dispatch));
			else
			{
				history_usage(dispatch);
				return (1);
			}
		}
		else
		{
			history_usage(dispatch);
			return (1);
		}
	}
	return (0);
}

int						built_history(t_dispatch *const dispatch, char **argv)
{
	register size_t		i;
	t_history_node		*ptr;

	if (history_option(dispatch, ++argv))
		return (0);
	i = 0;
	ptr = dispatch->history.array;
	while (i < dispatch->history.count)
	{
		ft_printf(">%5zd > %s\n", i++, ptr->src);
		ptr++;
	}
	return (0);
}
