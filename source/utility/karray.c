/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   karray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 09:53:14 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/29 11:44:51 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void		karray(char **split, int index, const int freed)
{
	if (freed)
		free(split[index]);
	if (split[index + 1])
	{
		while (split[index + 1])
		{
			split[index] = split[index + 1];
			index++;
		}
		split[index] = NULL;
	}
	else
		split[index] = NULL;
}
