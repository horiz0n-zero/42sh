/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 14:39:09 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/02 14:39:12 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void			display_lclear(t_dispatch *const dispatch)
{
	write(STDOUT_FILENO, dispatch->display.caps[CL].s,
						dispatch->display.caps[CL].l);
	SUPER(dispatch)->display.prompt(NULL, 0, dispatch);
	write(STDOUT_FILENO, dispatch->display.buffer, dispatch->display.len);
	dispatch->display.index = dispatch->display.len;
}
