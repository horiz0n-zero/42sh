/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stccjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 09:46:10 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/07 11:52:26 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void			*ft_stcjoin(const char *s1, const char *s2)
{
	static char	buffy[1024];
	char		*new;

	new = buffy;
	while (*s1)
		*new++ = *s1++;
	while (*s2)
		*new++ = *s2++;
	*new = 0;
	return (buffy);
}

void			*ft_stccjoin(const char *s1, const char *s2, const char c)
{
	static char	stc[1024];
	char		*ptr;

	ptr = stc;
	while (*s1)
		*ptr++ = *s1++;
	*ptr++ = c;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = 0;
	return (stc);
}
