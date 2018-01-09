/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_envguard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 12:52:51 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/11 16:37:43 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int					built_envguard(t_dispatch *const dispatch, char **argv)
{
	extern char		**environ;

	(void)argv;
	SUPER(dispatch)->env.guard(dispatch);
	SUPER(dispatch)->foreground.binaries.dtor(dispatch);
	SUPER(dispatch)->foreground.binaries.ctor(dispatch);
	SUPER(dispatch)->env.sort((int)SUPER(dispatch)->env.count(), environ);
	return (0);
}
