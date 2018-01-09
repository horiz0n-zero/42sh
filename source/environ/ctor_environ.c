/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:04:08 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/22 15:58:27 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void			env_shlvl(t_dispatch *const dispatch)
{
	extern char		**environ;
	int				i;
	int				n;
	char			*ptr;

	i = -1;
	n = 0;
	while (environ[++i])
		if (SUPER(dispatch)->env.corres("SHLVL", environ[i]))
		{
			ptr = environ[i];
			while (*ptr && *ptr != '=')
				ptr++;
			ptr++;
			while (*ptr >= '0' && *ptr <= '9')
				n = n * 10 + (*ptr++ - '0');
			n++;
			free(environ[i]);
			ptr = SUPER(dispatch)->string.itoa(n);
			environ[i] = ft_strjoin("SHLVL=", ptr);
			free(ptr);
			return ;
		}
}

void				ctor_environ(t_dispatch *const dispatch)
{
	extern char		**environ;
	char			**new;
	const size_t	count = SUPER(dispatch)->env.count();

	if (environ && count)
	{
		if (!(new = malloc(sizeof(char*) * (count + 1))))
			SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
		while (*environ)
			*new++ = SUPER(dispatch)->string.copy(*environ++);
		*new = NULL;
		environ = new - count;
		env_shlvl(dispatch);
	}
	SUPER(dispatch)->env.guard(dispatch);
	SUPER(dispatch)->env.sort((int)SUPER(dispatch)->env.count(), environ);
}
