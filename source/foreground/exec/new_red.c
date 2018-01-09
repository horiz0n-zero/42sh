/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_red.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 11:37:13 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/12 15:58:46 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const t_red		g_default_red =
{
	NULL,
	0,
	S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH,
	-1,
	-1,
	-1,
	-1,
	NULL
};

void					*new_red(void)
{
	t_red *const		red = malloc(sizeof(t_red));

	if (!red)
		malloc_exit();
	*red = g_default_red;
	return (red);
}
