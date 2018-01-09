/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:34:08 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/24 11:56:28 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void			dispatch_exit(t_dispatch *const dispatch, const char *err)
{
	SUPER(dispatch)->dtor(dispatch);
	if (err)
		ft_fprintf(STDERR_FILENO, "\33[38;5;202m%s\n", err);
	exit(1);
}
