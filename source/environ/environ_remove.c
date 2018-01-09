/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:26:46 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/15 15:44:33 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void			env_suppress(t_dispatch *const dispatch, const int index)
{
	extern char		**environ;
	const size_t	count = SUPER(dispatch)->env.count();
	char			**new;
	int				i;

	i = 0;
	new = malloc(sizeof(char*) * count);
	while (i != index)
		*new++ = environ[i++];
	free(environ[i++]);
	while (environ[i])
		*new++ = environ[i++];
	*new = NULL;
	free(environ);
	environ = new - count + 1;
}

void				environ_remove(t_dispatch *const dispatch,
		const char *const name)
{
	extern char		**environ;
	int				i;

	i = 0;
	while (environ[i])
	{
		if (SUPER(dispatch)->env.corres(name, environ[i]))
		{
			env_suppress(dispatch, i);
			return ;
		}
		i++;
	}
}
