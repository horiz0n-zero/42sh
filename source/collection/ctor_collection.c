/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor_collection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 09:10:02 by afeuerst          #+#    #+#             */
/*   Updated: 2017/10/18 16:43:42 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

void				ctor_collection(t_dispatch *const dispatch)
{
	dispatch->foreground.collection.task = NULL;
	dispatch->foreground.collection.ctask = NULL;
	dispatch->foreground.collection.ccmd = NULL;
}
