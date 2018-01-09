/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstoian <kstoian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:14:12 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/04 17:07:03 by kstoian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

char		*ft_strcjoin(const char *s1, const char *s2, const char c)
{
	char	*new;
	char	*ptr;

	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!new)
		malloc_exit();
	ptr = new;
	while (*s1)
		*ptr++ = *s1++;
	*ptr++ = c;
	while ((*ptr++ = *s2++))
		continue ;
	return (new);
}
