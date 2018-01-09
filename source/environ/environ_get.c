/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:48:32 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/06 16:27:40 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void			*environ_get(t_dispatch *const dispatch, const char *name)
{
	extern char	**environ;
	int			i;
	char		*ptr;

	i = 0;
	while (environ[i])
	{
		if (SUPER(dispatch)->env.corres(name, environ[i]))
		{
			ptr = environ[i];
			while (*ptr && *ptr != '=')
				ptr++;
			if (*ptr == '=')
				ptr++;
			return (ptr);
		}
		i++;
	}
	return (NULL);
}
