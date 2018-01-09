/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 14:55:27 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/21 15:07:29 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		string_swap(char *const src)
{
	int		s;
	int		e;

	s = 0;
	e = 0;
	while (src[e])
		e++;
	e--;
	while (e > s)
	{
		src[e] ^= src[s];
		src[s] ^= src[e];
		src[e--] ^= src[s++];
	}
}
