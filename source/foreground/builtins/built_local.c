/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_local.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:58:12 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/04 11:12:55 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int			built_local(t_dispatch *const dispatch, char **argv)
{
	size_t	i;

	i = 0;
	(void)argv;
	write(STDOUT_FILENO, "\33[38;5;244m", sizeof("\33[38;5;244m"));
	while (i < dispatch->var.count)
	{
		if (environ_get(dispatch, dispatch->var.local[i].key))
			ft_printf("exported : ");
		ft_printf("%s='%s'\n", dispatch->var.local[i].key,
				dispatch->var.local[i].value);
		i++;
	}
	write(STDOUT_FILENO, "\33[37m", sizeof("\33[37m"));
	return (0);
}
