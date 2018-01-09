/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ktoken.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 11:45:21 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/29 11:47:22 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		ktoken(t_token *ptr, int index, const int freed)
{
	if (freed)
		free(ptr[index].src);
	if (ptr[index + 1].src)
	{
		while (ptr[index + 1].src)
		{
			ptr[index] = ptr[index + 1];
			index++;
		}
		ptr[index].src = NULL;
	}
	else
		ptr[index].src = NULL;
}
