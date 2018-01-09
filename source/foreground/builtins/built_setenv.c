/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_setenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 13:28:44 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/23 10:01:48 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const char		*g_usage[] =
{
	"setenv [arguments...]\n",
	"setenv will add every argument to the environement.\n",
	"arguments format : NAME VALUE.\n"
};

static size_t			g_usage_size[] =
{
	sizeof("setenv [arguments...]\n"),
	sizeof("setenv will add every argument to the environement.\n"),
	sizeof("arguments format : NAME=VALUE.\n")
};

static inline int		usage_setenv(t_dispatch *const dispatch)
{
	write(STDERR_FILENO, dispatch->display.properties.builtins_color,
				ft_strlen(dispatch->display.properties.builtins_color));
	write(STDERR_FILENO, g_usage[0], g_usage_size[0]);
	write(STDERR_FILENO, g_usage[1], g_usage_size[1]);
	write(STDERR_FILENO, g_usage[2], g_usage_size[2]);
	return (0);
}

int						built_setenv(t_dispatch *const dispatch, char **argv)
{
	extern char			**environ;

	argv++;
	if (*argv && *(argv + 1))
		while (1)
		{
			SUPER(dispatch)->env.append(dispatch, *argv, *(argv + 1));
			argv += 2;
			if (*argv && *(argv + 1))
				continue ;
			else
				break ;
		}
	else
		return (usage_setenv(dispatch));
	SUPER(dispatch)->foreground.binaries.dtor(dispatch);
	SUPER(dispatch)->foreground.binaries.ctor(dispatch);
	SUPER(dispatch)->env.sort((int)SUPER(dispatch)->env.count(), environ);
	return (0);
}
