/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_kpush.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:58:26 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/02 15:58:28 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		string_kpush(char *src, const int index)
{
	char	*ptr;

	ptr = src + index;
	*ptr++ = 0;
	while (*ptr)
	{
		*(ptr - 1) = *ptr;
		ptr++;
	}
	*(ptr - 1) = 0;
}
