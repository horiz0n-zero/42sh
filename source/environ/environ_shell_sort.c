/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_shell_sort.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:28:29 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/09 08:37:30 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static int	sort_cmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return ((int)*s1 - *s2);
		s1++;
		s2++;
	}
	return ((int)*s1 - *s2);
}

void		environ_shell_sort(const int count, char **array)
{
	int		i;
	int		j;
	int		space;
	char	*tmp;

	space = count / 2;
	i = 0;
	j = space;
	while (j > 0)
	{
		while (j < count)
		{
			if (sort_cmp(array[j], array[i]) > 0)
			{
				tmp = array[j];
				array[j] = array[i];
				array[i] = tmp;
			}
			i++;
			j++;
		}
		i = 0;
		j = --space;
	}
}
