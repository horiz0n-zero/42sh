/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtor_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 11:54:38 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/14 11:51:42 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void			dtor_background(t_dispatch *const dispatch)
{
	t_back		*ptr;
	int			i;

	ptr = dispatch->foreground.background.back;
	while (ptr)
	{
		kill(ptr->pid, SIGKILL);
		ft_printf("\33[38;2;255;23;23mkill %s\n", *ptr->argv);
		i = 0;
		while (ptr->argv[i])
			free(ptr->argv[i++]);
		free(ptr->argv);
		ptr = ptr->next;
	}
	free(dispatch->foreground.background.pids);
}
