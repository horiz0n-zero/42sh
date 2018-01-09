/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_sleep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:01:56 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/10 13:58:23 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				dispatch_sleep(const time_t secs, const long nsecs)
{
	struct timespec	spec;
	struct timespec	tmp;

	spec.tv_sec = secs;
	spec.tv_nsec = nsecs;
	nanosleep(&spec, &tmp);
}
