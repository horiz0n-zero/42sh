/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtor_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:09:18 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/06 16:25:41 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				dtor_environ(t_dispatch *const dispatch)
{
	extern char		**environ;
	int				i;

	(void)dispatch;
	i = 0;
	while (environ[i])
		free(environ[i++]);
	free(environ);
}
