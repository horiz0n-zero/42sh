/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unsetenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 13:25:40 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/23 10:01:18 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const char		*g_usage[] =
{
	"unsetenv [arguments ...]\n",
	"unsetenv will remove every argument in the environement.\n",
	"arguments format : VALUE\33[37m\n"
};

static const size_t		g_usage_size[] =
{
	sizeof("unsetenv [arguments ...]\n"),
	sizeof("unsetenv will remove every argument in the environement.\n"),
	sizeof("arguments format : VALUE\33[37m\n")
};

static inline void		unsetenv_usage(t_dispatch *const dispatch)
{
	write(STDERR_FILENO, dispatch->display.properties.builtins_color,
				ft_strlen(dispatch->display.properties.builtins_color));
	write(STDERR_FILENO, g_usage[0], g_usage_size[0]);
	write(STDERR_FILENO, g_usage[1], g_usage_size[1]);
	write(STDERR_FILENO, g_usage[2], g_usage_size[2]);
}

int						built_unsetenv(t_dispatch *const dispatch, char **argv)
{
	if (*++argv)
		while (*argv)
			SUPER(dispatch)->env.remove(dispatch, *argv++);
	else
	{
		unsetenv_usage(dispatch);
		return (0);
	}
	SUPER(dispatch)->foreground.binaries.dtor(dispatch);
	SUPER(dispatch)->foreground.binaries.ctor(dispatch);
	return (0);
}
