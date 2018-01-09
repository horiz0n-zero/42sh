/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:58:40 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/02 15:58:57 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		*string_copy(const char *src)
{
	char	*new;
	char	*ptr;

	new = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!new)
		malloc_exit();
	ptr = new;
	while ((*ptr++ = *src++))
		continue ;
	return (new);
}
