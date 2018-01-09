/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_append.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 11:37:34 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 15:38:42 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void	*argv_copy(char **const argv)
{
	size_t	i;
	char	**new;

	i = 0;
	while (argv[i])
		i++;
	if (!(new = malloc(sizeof(char*) * (i + 1))))
		malloc_exit();
	i = 0;
	while (argv[i])
	{
		new[i] = string_copy(argv[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void		background_append(t_dispatch *const dispatch, t_cmd *const cmd,
		const int status)
{
	t_back	*new;
	t_back	*ptr;

	new = malloc(sizeof(t_back));
	if (!new)
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	new->pid = cmd->pid;
	new->status = status;
	new->argv = argv_copy(cmd->argv);
	new->next = NULL;
	if (!dispatch->foreground.background.back)
		dispatch->foreground.background.back = new;
	else
	{
		ptr = dispatch->foreground.background.back;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}
