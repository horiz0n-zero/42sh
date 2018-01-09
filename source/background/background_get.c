/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 11:44:55 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 15:38:24 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

t_back			*background_get(t_dispatch *const dispatch, const pid_t pid)
{
	t_back		*ptr;

	ptr = dispatch->foreground.background.back;
	while (ptr)
	{
		if (ptr->pid == pid)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}
