/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenscopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 14:15:33 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/29 14:23:04 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static size_t		tokenscopy_count(t_token *ptr)
{
	size_t			count;

	count = 0;
	while (ptr[count].src)
		count++;
	return (count);
}

void				*tokenscopy(t_token *ptr)
{
	const size_t	count = tokenscopy_count(ptr);
	t_token			*copy;
	size_t			i;

	i = 0;
	if (!(copy = malloc(sizeof(t_token) * (count + 1))))
		malloc_exit();
	while (ptr[i].src)
	{
		copy[i] = ptr[i];
		i++;
	}
	copy[i].src = NULL;
	return (copy);
}
