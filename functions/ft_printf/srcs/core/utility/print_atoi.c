/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:42:44 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/16 12:57:08 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"

uint32_t		atoi_print(uint64_t *const value, const char *const src,
		uint32_t index)
{
	uint64_t	raw;

	raw = 0;
	while (src[index] >= '0' && src[index] <= '9')
		raw = raw * 10 + (((uint64_t)(src[index++] - '0')) & 0xFF);
	*value = raw;
	return (index);
}
