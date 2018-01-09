/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_append_pid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 11:11:39 by afeuerst          #+#    #+#             */
/*   Updated: 2017/10/17 14:12:52 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void	background_expand_pids(t_dispatch *const dispatch)
{
	pid_t	*current;
	size_t	index;

	index = 0;
	current = dispatch->foreground.background.pids;
	dispatch->foreground.background.pids_size *= 2;
	dispatch->foreground.background.pids = malloc(sizeof(pid_t) *
			dispatch->foreground.background.pids_size);
	if (!dispatch->foreground.background.pids)
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	while (index < dispatch->foreground.background.pids_count)
	{
		dispatch->foreground.background.pids[index] = current[index];
		index++;
	}
	free(current);
}

void		background_append_pid(t_dispatch *const dispatch, const pid_t pid)
{
	pid_t	*ptr;

	if (dispatch->foreground.background.pids_count + 1 >
			dispatch->foreground.background.pids_size)
		background_expand_pids(dispatch);
	ptr = dispatch->foreground.background.pids;
	ptr[dispatch->foreground.background.pids_count++] = pid;
}
