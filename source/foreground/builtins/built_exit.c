/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:39:08 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/06 14:33:20 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int				built_exit(t_dispatch *const dispatch, char **argv)
{
	int			status;

	status = 0;
	if (*++argv)
	{
		status = SUPER(dispatch)->string.atoi(*argv);
		if (status < 0)
			status = 0;
	}
	SUPER(dispatch)->display.dtor(dispatch);
	SUPER(dispatch)->foreground.dtor(dispatch);
	SUPER(dispatch)->history.dtor(dispatch);
	SUPER(dispatch)->var.dtor(dispatch);
	SUPER(dispatch)->env.dtor(dispatch);
	exit(status);
}
