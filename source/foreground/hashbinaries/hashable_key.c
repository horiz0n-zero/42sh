/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashable_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 14:44:35 by afeuerst          #+#    #+#             */
/*   Updated: 2017/09/07 15:25:36 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

size_t		hashable_key(const char *src)
{
	size_t	key;

	key = 0xF245F;
	if (!src)
		return (0);
	while (*src)
	{
		key ^= (size_t)*src++;
		key <<= 1;
		key += (size_t)*src;
	}
	return (key);
}
