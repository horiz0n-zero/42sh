/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_isvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 09:59:44 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/06 10:10:13 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int				var_isvar(register const char *src)
{
	while (*src)
		if (*src++ == '=')
			return (true);
	return (false);
}
