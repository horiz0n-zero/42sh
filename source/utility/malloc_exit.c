/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:27:53 by afeuerst          #+#    #+#             */
/*   Updated: 2017/09/07 15:28:45 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void					malloc_exit(void)
{
	t_dispatch *const	dis = get_dispatch(NULL);

	SUPER(dis)->exit(dis, REQ_MALLOC);
}
