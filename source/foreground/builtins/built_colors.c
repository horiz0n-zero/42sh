/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 08:52:55 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/08 11:18:25 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const size_t				g_pointee[256] =
{
	['l'] = offsetof(struct s_dispatch, display.properties.location_color),
	['s'] = offsetof(struct s_dispatch, display.properties.separator_color),
	['p'] = offsetof(struct s_dispatch, display.properties.prompt_color),
	['t'] = offsetof(struct s_dispatch, display.properties.text_color),
	['b'] = offsetof(struct s_dispatch, display.properties.builtins_color)
};

static void						colors_show_colors(t_dispatch *const dispatch)
{
	static const char			showl[] = "-l%s location color.\33[37m\n";
	static const char			shows[] = "-s%s separator color.\33[37m\n";
	static const char			showp[] = "-p%s prompt color.\33[37m\n";
	static const char			showt[] = "-t%s text color.\33[37m\n";
	static const char			showb[] = "-b%s builtins color.\33[37m\n";

	ft_printf("%s", "colors : show, select colors\n");
	ft_printf(showl, dispatch->display.properties.location_color);
	ft_printf(shows, dispatch->display.properties.separator_color);
	ft_printf(showp, dispatch->display.properties.prompt_color);
	ft_printf(showt, dispatch->display.properties.text_color);
	ft_printf(showb, dispatch->display.properties.builtins_color);
}

static void						colors_assign(t_dispatch *const dispatch,
		const size_t ass)
{
	char **const				ptr = (void*)((char*)dispatch + ass);
	char *const					color = colors_select(dispatch);

	if (!color)
	{
		ft_printf("%s : No color selected.\n", "colors");
		return ;
	}
	if (*ptr)
		free(*ptr);
	*ptr = color;
	ft_printf("%s\r%s\n", CAPS(UP).s, CAPS(CD).s);
}

int								built_colors(t_dispatch *const dispatch,
		char **argv)
{
	size_t						assign;

	if (*++argv)
	{
		if (**argv == '-')
		{
			if ((assign = g_pointee[(int)*(*argv + 1)]))
				colors_assign(dispatch, assign);
			else
				ft_printf("colors : Bad option : %s\n", *argv);
		}
	}
	else
		colors_show_colors(dispatch);
	return (0);
}
