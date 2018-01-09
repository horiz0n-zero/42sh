/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:36:07 by afeuerst          #+#    #+#             */
/*   Updated: 2017/10/17 14:22:08 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

char					*environ_pwd(t_dispatch *const dispatch)
{
	static char			env_pwd[1024];

	(void)dispatch;
	if (!getcwd(env_pwd, 1024))
		return ("/");
	return (env_pwd);
}
