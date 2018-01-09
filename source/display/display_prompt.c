/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:34:45 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/16 15:22:26 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				display_prompt(const char *pr, const size_t indes,
		t_dispatch *const dispatch)
{
	static char		hereweare[2048];

	if (pr)
	{
		write(STDOUT_FILENO, pr, ft_strlen(pr));
		dispatch->display.indes = indes;
	}
	else
	{
		getcwd(hereweare, 2048);
		ft_printf("%s%s %s%s %sat %s%s\n%s%s %s",
				dispatch->display.properties.separator_color,
				dispatch->display.properties.separator_string,
				dispatch->display.properties.location_color, hereweare,
				dispatch->display.properties.separator_color,
				dispatch->display.properties.location_color,
				dispatch->display.node.nodename,
				dispatch->display.properties.prompt_color,
				dispatch->display.properties.prompt_string,
				dispatch->display.properties.text_color);
		dispatch->display.indes = 2;
	}
}
