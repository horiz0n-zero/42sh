/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_astrpush.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:09:52 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/12 10:28:59 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				string_astrpush(const char *src, char *dst, int index)
{
	const int		i = index;
	const size_t	len = ft_strlen(src);

	if (dst[index])
	{
		while (dst[index])
			index++;
		while (i <= index && index > 0)
		{
			index--;
			dst[(size_t)index + len] = dst[index];
		}
	}
	while (*src)
		*(dst++ + i) = *src++;
}
