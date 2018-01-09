/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_and.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 13:37:04 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/16 16:56:12 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void			red_and(t_dispatch *const dispatch, t_red *const red)
{
	int			i;

	red->flag |= R_ISRAT;
	if (TOKENSRC && *TOKENSRC >= '0' && *TOKENSRC <= '9')
	{
		i = 0;
		red->y = 0;
		while (TOKENSRC[i] >= '0' && TOKENSRC[i] <= '9')
			red->y = red->y * 10 + (TOKENSRC[i++] - '0');
		if (red->y > 2)
			red->y = STDERR_FILENO;
		if (TOKENSRC[i] == '-')
			red->flag |= R_CLOSED;
		ktoken(dispatch->foreground.tokens, dispatch->foreground.index, true);
	}
	else
		red->y = STDERR_FILENO;
	if (TOKENSRC && *TOKENSRC == '-' && !*(TOKENSRC + 1))
	{
		red->flag |= R_CLOSED;
		ktoken(dispatch->foreground.tokens, dispatch->foreground.index, true);
	}
}
