/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 10:17:46 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/06 14:51:40 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static size_t	var_exist(t_dispatch *const dispatch, const char *key)
{
	size_t		i;

	i = 0;
	while (i < dispatch->var.count)
	{
		if (!ft_strcmp(key, dispatch->var.local[i].key))
			return (i);
		i++;
	}
	return (42000);
}

static void		var_add(t_dispatch *const dispatch, char *const key,
		char *const value)
{
	if (dispatch->var.size < dispatch->var.count + 1)
		SUPER(dispatch)->var.expand(dispatch);
	dispatch->var.local[dispatch->var.count].key = key;
	dispatch->var.local[dispatch->var.count].value = value;
	dispatch->var.count++;
}

void			var_append(t_dispatch *const dispatch, const char *src)
{
	char *const	data = SUPER(dispatch)->string.copy(src);
	int			i;
	size_t		index;

	i = 0;
	while (data[i] && data[i] != '=')
		i++;
	data[i++] = 0;
	if ((index = var_exist(dispatch, data)) != 42000)
	{
		free(dispatch->var.local[index].key);
		dispatch->var.local[index].key = data;
		dispatch->var.local[index].value = data + i;
	}
	else
		var_add(dispatch, data, data + i);
}
