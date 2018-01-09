/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor_dispatch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:34:02 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 15:37:28 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void	dispatch_prepare_base(t_dispatch *const dispatch)
{
	char			*src;

	src = getenv("HOME");
	if (src)
	{
		src = ft_stcjoin(src, "/.42sh/");
		mkdir(src, S_IRWXU | S_IRWXG | S_IROTH);
		dispatch->base = string_copy(src);
	}
	else
		dispatch->base = NULL;
}

static inline void	dispatch_fd(t_dispatch *const dispatch)
{
	(void)dispatch;
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO) ||
			!isatty(STDERR_FILENO))
	{
		ft_fprintf(STDOUT_FILENO, ":P\n");
		exit(EXIT_SUCCESS);
	}
}

void				ctor_dispatch(t_dispatch *const dispatch,
		const void *const self)
{
	dispatch->self = self;
	dispatch_fd(dispatch);
	dispatch_prepare_base(dispatch);
	SUPER(dispatch)->env.ctor(dispatch);
	SUPER(dispatch)->display.ctor(dispatch);
	SUPER(dispatch)->foreground.ctor(dispatch);
	SUPER(dispatch)->history.ctor(dispatch);
	SUPER(dispatch)->var.ctor(dispatch);
	dispatch->string.random = open("/dev/random", O_RDONLY);
}
