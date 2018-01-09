/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:27:03 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/06 16:26:32 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

size_t			environ_count(void)
{
	extern char	**environ;
	size_t		size;

	size = 0;
	while (environ[size])
		size++;
	return (size);
}
