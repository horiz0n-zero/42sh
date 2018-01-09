/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_corres.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 10:22:44 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/07 10:25:26 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int			environ_corres(const char *name, const char *env)
{
	while (*name && *env && *env != '=')
	{
		if (*name != *env)
			return (0);
		name++;
		env++;
	}
	if (*env == '=')
		return (1);
	return (0);
}
