/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histo_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 11:36:56 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/11 12:14:34 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void	histo_kpush(t_dispatch *const dispatch, const int index)
{
	int		i;

	i = index;
	free(dispatch->history.array[i].src);
	while (i < (int)(dispatch->history.count - 1))
	{
		dispatch->history.array[i] = dispatch->history.array[i + 1];
		i++;
	}
	dispatch->history.count--;
}

int			histo_d(t_dispatch *const dispatch, char **argv)
{
	int		n;

	if (*++argv)
	{
		n = SUPER(dispatch)->string.atoi(*argv);
		if (n < 0 || n >= (int)(dispatch->history.count + 1))
			ft_fprintf(STDERR_FILENO, "bad number %d\n", n);
		else
			histo_kpush(dispatch, n);
	}
	else
		ft_fprintf(STDERR_FILENO, "please specify a number.\n");
	return (1);
}
