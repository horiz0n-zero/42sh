/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtor_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstoian <kstoian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:35:22 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/05 14:30:34 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		dtor_display(t_dispatch *const dispatch)
{
	write(STDOUT_FILENO, CAPS(TE).s, CAPS(TE).l);
	if (dispatch->display.pasteboard)
		free(dispatch->display.pasteboard);
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &dispatch->display.saved) == -1)
		SUPER(dispatch)->exit(dispatch, "can't set the original term struct\n");
	if (dispatch->display.colors != -1)
		SUPER(dispatch)->display.writecolor(dispatch);
	free(dispatch->display.properties.location_color);
	free(dispatch->display.properties.separator_string);
	free(dispatch->display.properties.separator_color);
	free(dispatch->display.properties.prompt_string);
	free(dispatch->display.properties.prompt_color);
	free(dispatch->display.properties.text_color);
	free(dispatch->display.properties.builtins_color);
}
