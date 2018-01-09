/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 13:39:03 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/02 14:28:32 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int			built_echo(t_dispatch *const dispatch, char **argv)
{
	int		new;

	(void)dispatch;
	new = 1;
	if (*++argv)
	{
		if (**argv == '-' && *(*argv + 1) == 'n')
		{
			new = 0;
			argv++;
		}
		while (*argv)
		{
			write(STDOUT_FILENO, *argv, ft_strlen(*argv));
			if (*++argv)
				write(STDOUT_FILENO, " ", 1);
		}
	}
	if (new)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
