/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ismultipleof.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeblonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 14:59:12 by jeblonde          #+#    #+#             */
/*   Updated: 2017/11/02 14:59:23 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

int			ft_ismultipleof(size_t number, size_t of)
{
	while (number > of)
		number -= of;
	if (number == of || !number)
		return (1);
	return (0);
}
