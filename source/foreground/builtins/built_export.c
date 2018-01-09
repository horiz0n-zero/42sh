/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstoian <kstoian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:51:26 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/04 16:55:57 by kstoian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static int	get_var(t_dispatch *const dispatch, const char *const key)
{
	int			index;

	index = 0;
	while (index < (int)dispatch->var.count)
	{
		if (!ft_strcmp(key, dispatch->var.local[index].key))
			return (index);
		index++;
	}
	return (-1);
}

int			built_export(t_dispatch *const dispatch, char **argv)
{
	t_var	*var;
	int		i;

	if (*++argv)
	{
		while (*argv)
		{
			i = get_var(dispatch, *argv);
			if (i == -1)
			{
				ft_fprintf(STDERR_FILENO, "unexportable : %s\n", *argv++);
				continue ;
			}
			var = dispatch->var.local + i;
			SUPER(dispatch)->env.append(dispatch, var->key, var->value);
			argv++;
		}
	}
	return (0);
}
