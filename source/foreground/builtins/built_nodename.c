/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_nodename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 10:32:29 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/12 10:34:35 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int			built_nodename(t_dispatch *const dispatch, char **argv)
{
	(void)argv;
	ft_printf("%s\n%s\n%s\n%s\n%s\n",
			dispatch->display.node.sysname,
			dispatch->display.node.nodename,
			dispatch->display.node.release,
			dispatch->display.node.version,
			dispatch->display.node.machine);
	return (0);
}
