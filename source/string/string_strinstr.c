/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_strinstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:34:54 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/22 16:28:55 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int						string_strinstr(register const char *in,
		register const char *find)
{
	const char *const	start = find;

	while (*in)
	{
		if (*in == *find)
		{
			while (*in && *find && *in == *find)
			{
				in++;
				find++;
			}
			if (!*find)
				return (true);
			find = start;
		}
		else
			in++;
	}
	return (false);
}
