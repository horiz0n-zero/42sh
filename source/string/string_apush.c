/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:36:52 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/02 15:57:26 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		string_apush(char *src, const int index, const char c)
{
	size_t	slen;

	src += index;
	slen = 0;
	if (*src)
	{
		while (src[slen])
			slen++;
		while (slen > 0)
		{
			src[slen] = src[slen - 1];
			slen--;
		}
		*src = c;
	}
	else
		*src = c;
}
