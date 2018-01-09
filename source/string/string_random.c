/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_random.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 16:52:09 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/04 13:52:24 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

char					*string_random(t_dispatch *const dispatch, size_t len,
		const char *prefix)
{
	static char			buffy[42];
	static const char	chars[] = "ABCDEF*0123456789";
	static const int	chars_size = sizeof(chars) - 1;
	int					i;
	int					index;

	i = 0;
	read(dispatch->string.random, buffy + ft_strlen(prefix), len);
	while (*prefix)
		buffy[i++] = *prefix++;
	while (len--)
	{
		index = ((int)buffy[i] % chars_size) & 0xF;
		buffy[i] = chars[index];
		i++;
	}
	buffy[i] = 0;
	return (buffy);
}
