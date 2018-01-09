/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_home.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 14:20:52 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/07 11:18:31 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

char				*environ_home(t_dispatch *const dispatch)
{
	struct passwd	*pass;

	(void)dispatch;
	pass = getpwuid(getuid());
	if (!pass)
		return ("???");
	return (pass->pw_dir);
}
