/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokensinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 12:02:22 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/30 13:16:09 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static size_t			array_count(t_token *ptr)
{
	size_t				count;

	count = 0;
	while (ptr->src)
	{
		ptr++;
		count++;
	}
	return (count);
}

void					tokensinsert(t_dispatch *const dispatch,
		t_token *insert)
{
	const size_t		dis_size = array_count(dispatch->foreground.tokens);
	const size_t		in_size = array_count(insert);
	t_token				*new;
	int					i;
	int					index;

	i = 0;
	index = dispatch->foreground.index;
	if (!(new = malloc(sizeof(t_token) * (dis_size + in_size + 1))))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	while (i < index)
	{
		new[i] = dispatch->foreground.tokens[i];
		i++;
	}
	while (insert->src)
		new[i++] = *insert++;
	while (dispatch->foreground.tokens[index].src)
		new[i++] = dispatch->foreground.tokens[index++];
	new[i].src = NULL;
	free(dispatch->foreground.tokens);
	dispatch->foreground.tokens = new;
}
