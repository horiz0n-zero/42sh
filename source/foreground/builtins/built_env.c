/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 13:20:25 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/02 15:15:37 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int						built_env(t_dispatch *const dispatch, char **argv)
{
	extern char			**environ;
	char				**ptr;

	(void)dispatch;
	(void)argv;
	if (!environ)
		return (1);
	ptr = environ;
	while (*ptr)
	{
		write(STDOUT_FILENO, *ptr, ft_strlen(*ptr));
		write(STDOUT_FILENO, "\n", 1);
		ptr++;
	}
	return (0);
}
