/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dispatch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:37:26 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/02 14:57:49 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				*get_dispatch(void *const dispatch)
{
	static void		*ptr = NULL;

	if (!ptr)
		ptr = dispatch;
	return (ptr);
}
