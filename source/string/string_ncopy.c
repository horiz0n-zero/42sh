/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_ncopy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 10:10:55 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/05 10:20:38 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void			*string_ncopy(const char *src, size_t n)
{
	char		*new;
	char		*ptr;

	if (!(new = malloc(n + 1)))
		malloc_exit();
	ptr = new;
	while (n--)
		*new++ = *src++;
	*new = 0;
	return (ptr);
}
