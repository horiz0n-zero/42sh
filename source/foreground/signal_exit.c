/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:36:42 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/07 10:05:14 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void						signal_exit(int signal)
{
	t_dispatch *const		dispatch = get_dispatch(NULL);

	(void)signal;
	SUPER(dispatch)->dtor(dispatch);
}
