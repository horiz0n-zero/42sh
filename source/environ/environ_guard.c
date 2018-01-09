/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_guard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:36:00 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/15 15:44:50 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const t_guard	g_guard[] =
{
	{"PATH", NULL,
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"},
	{"PWD", environ_pwd, NULL},
	{"OLDPWD", environ_pwd, NULL},
	{"TERM", NULL, "xterm-256color"},
	{"SHLVL", NULL, "1"},
	{"HOME", environ_home, NULL},
	{"CLICOLOR", NULL, "true"}
};

static void				environ_default(t_dispatch *const dispatch)
{
	extern char			**environ;
	size_t				i;
	static const size_t	count = sizeof(g_guard) / sizeof(g_guard[0]);

	i = 0;
	environ = malloc(sizeof(char*) * (count + 1));
	if (!environ)
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	ft_memset((void*)environ, sizeof(char*) * (count + 1));
	while (i < count)
	{
		if (!g_guard[i].get)
			environ[i] = ft_strcjoin(g_guard[i].name, g_guard[i].default_name,
					'=');
		else
			environ[i] = ft_strcjoin(g_guard[i].name,
					g_guard[i].get(dispatch), '=');
		i++;
	}
	environ[i] = NULL;
}

void					environ_guard(t_dispatch *const dispatch)
{
	extern char			**environ;
	static const int	count = sizeof(g_guard) / sizeof(g_guard[0]);
	const size_t		size = SUPER(dispatch)->env.count();
	int					i;
	char				*add;

	if (!environ || !size)
	{
		environ_default(dispatch);
		return ;
	}
	i = 0;
	while (i < count)
	{
		if (!SUPER(dispatch)->env.get(dispatch, g_guard[i].name))
		{
			if (g_guard[i].get)
				add = g_guard[i].get(dispatch);
			else
				add = g_guard[i].default_name;
			SUPER(dispatch)->env.append(dispatch, g_guard[i].name, add);
		}
		i++;
	}
}
