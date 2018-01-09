/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_atoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:08:09 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/09 15:12:46 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int			string_atoi(const char *src)
{
	int		n;
	int		nega;

	n = 0;
	if (*src == '-' && src++)
		nega = 1;
	else
		nega = 0;
	while (*src >= '0' && *src <= '9')
		n = n * 10 + (*src++ - '0');
	return (n);
}
