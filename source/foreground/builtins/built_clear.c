/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 14:36:27 by afeuerst          #+#    #+#             */
/*   Updated: 2017/10/17 14:36:35 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int				built_clear(t_dispatch *const dispatch, char **argv)
{
	write(STDOUT_FILENO, dispatch->display.caps[CL].s,
						dispatch->display.caps[CL].l);
	(void)argv;
	return (0);
}
