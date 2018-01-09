/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_herestring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:01:19 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 15:10:27 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void			red_herestring(t_dispatch *const dispatch, t_red *const red)
{
	int			fd;
	char		*name;

	name = SUPER(dispatch)->string.random(dispatch, 15, "/tmp/.42sh_");
	fd = open(name, O_CREAT | O_TRUNC | O_RDWR, dispatch->foreground.red_mode);
	red->flag |= R_HERE;
	write(fd, red->file, ft_strlen(red->file));
	close(fd);
	free(red->file);
	red->file = SUPER(dispatch)->string.copy(name);
}
