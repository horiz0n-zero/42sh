/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstoian <kstoian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 13:46:46 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/04 18:38:08 by kstoian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static char			*get_txt(t_dispatch *const dispatch, int *const stop)
{
	char *const		buffer = dispatch->display.buffer;
	const size_t	buffer_size = dispatch->display.buffer_size;
	const size_t	index = dispatch->display.index;
	const size_t	len = dispatch->display.len;
	char			*txt;

	if (!(dispatch->display.buffer = malloc(dispatch->display.buffer_size + 1)))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	ft_memset(dispatch->display.buffer, dispatch->display.buffer_size + 1);
	dispatch->display.index = 0;
	dispatch->display.len = 0;
	dispatch->display.indes = sizeof("heredoc > ") - 1;
	write(STDOUT_FILENO, "heredoc > ", dispatch->display.indes);
	SUPER(dispatch)->display.here_loop(dispatch, stop);
	txt = dispatch->display.buffer;
	dispatch->display.buffer = buffer;
	dispatch->display.buffer_size = buffer_size;
	dispatch->display.len = len;
	dispatch->display.index = index;
	return (txt);
}

static void			prepare_result(t_dispatch *const dispatch, t_red *const red,
		char **const ptr)
{
	int				file;
	char			*n;
	char *const		src = ptr[1] ? ptr[1] : "";

	n = SUPER(dispatch)->string.random(dispatch, 15, "/tmp/.42sh_");
	file = open(n, O_CREAT | O_TRUNC | O_RDWR, dispatch->foreground.red_mode);
	write(file, src, ft_strlen(src));
	close(file);
	free(red->file);
	red->file = SUPER(dispatch)->string.copy(n);
}

static int			herestop(const char *get, const char *world, const int stop)
{
	if (stop)
		return (stop);
	while (*get && *world && *get == *world)
	{
		get++;
		world++;
	}
	if ((*get == '\n' || !*get) && !*world)
		return (1);
	return (0);
}

static inline void	ll_loop(t_dispatch *const dispatch, t_red *const red,
		int *const stop, char **const ptr)
{
	while (1)
	{
		ptr[0] = get_txt(dispatch, stop);
		if (herestop(ptr[0], red->file, *stop))
		{
			prepare_result(dispatch, red, ptr);
			free(ptr[0]);
			if (ptr[1])
				return (free(ptr[1]));
			else
				return ;
		}
		else
		{
			if (!ptr[1])
				ptr[1] = ptr[0];
			else
			{
				ptr[2] = ft_strjoin(ptr[1], ptr[0]);
				free(ptr[1]);
				free(ptr[0]);
				ptr[1] = ptr[2];
			}
		}
	}
}

void				red_heredoc(t_dispatch *const dispatch, t_red *const red)
{
	int				stop[2];
	char			*ptr[3];

	stop[0] = 0;
	stop[1] = red->x;
	ptr[0] = NULL;
	ptr[1] = NULL;
	ptr[2] = NULL;
	red->flag |= R_HERE;
	ll_loop(dispatch, red, stop, ptr);
}
