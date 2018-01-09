/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:26:03 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/15 15:44:01 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void			env_add(t_dispatch *const dispatch, char *const add)
{
	extern char		**environ;
	const size_t	count = SUPER(dispatch)->env.count();
	char			**new;
	int				i;

	i = 0;
	new = malloc(sizeof(char*) * (count + 2));
	while (environ[i])
	{
		new[i] = environ[i];
		i++;
	}
	new[i++] = add;
	new[i] = NULL;
	free(environ);
	environ = new;
}

void				environ_append(t_dispatch *const dispatch,
		const char *name, const char *value)
{
	extern char		**environ;
	int				i;
	char *const		new = ft_strcjoin(name, value, '=');

	i = 0;
	while (environ[i])
	{
		if (SUPER(dispatch)->env.corres(name, environ[i]))
		{
			free(environ[i]);
			environ[i] = new;
			return ;
		}
		i++;
	}
	env_add(dispatch, new);
}
