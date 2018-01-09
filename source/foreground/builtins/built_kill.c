/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_kill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:49:43 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/05 15:12:27 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int						built_kill(t_dispatch *const dispatch, char **argv)
{
	pid_t				pid;
	extern char			**environ;
	char				**pargv;
	int					i;

	i = 0;
	pargv = SUPER(dispatch)->foreground.background.percent(dispatch, argv);
	pid = fork();
	dispatch->foreground.background.turn = true;
	if (!pid)
	{
		*pargv = "/bin/kill";
		execve(*pargv, pargv, environ);
		ft_printf(FATAL_EXECVE, *argv, dispatch);
		exit(1);
	}
	else
		waitpid(pid, &dispatch->foreground.status, dispatch->foreground.wait);
	while (pargv[i])
		free(pargv[i++]);
	free(pargv);
	return (dispatch->foreground.status);
}
