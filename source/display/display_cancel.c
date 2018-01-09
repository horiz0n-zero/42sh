/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_cancel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 10:33:34 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/02 14:32:59 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		display_cancel(t_dispatch *const dispatch)
{
	SUPER(dispatch)->display.end(dispatch);
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size + 1);
	dispatch->display.len = 0;
	dispatch->display.index = 0;
	write(STDOUT_FILENO, "\n", 1);
	SUPER(dispatch)->display.prompt(NULL, 0, dispatch);
}
