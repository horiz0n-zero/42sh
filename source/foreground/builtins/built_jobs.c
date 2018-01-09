/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:55:06 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 14:33:44 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void	print_job(t_dispatch *const dispatch,
		const t_back *const back)
{
	int				i;

	i = 0;
	ft_printf("%s>> %-5d > %s%s\t", dispatch->display.properties.prompt_color,
			back->pid, back->status & B_STOPPED ?
			"\33[38;2;223;223;13mstopped" : "\33[38;2;0;255;42mrunning",
			dispatch->display.properties.location_color);
	while (back->argv[i])
		ft_printf("%s ", back->argv[i++]);
	ft_printf("\n\33[37m");
}

static void			jobs_argv(t_dispatch *const dispatch, char **argv)
{
	char			**pargv;
	int				i;
	t_back			*ptr;

	i = 0;
	if (!(pargv =
				SUPER(dispatch)->foreground.background.percent(dispatch, argv)))
		return ;
	while (pargv[i])
	{
		if (*pargv[i] >= '0' && *pargv[i] <= '9')
		{
			ptr = SUPER(dispatch)->foreground.background.get(dispatch,
					SUPER(dispatch)->string.atoi(pargv[i]));
			if (ptr)
				print_job(dispatch, ptr);
			else
				ft_printf("%sNo such process %s.\33[37m\n",
						dispatch->display.properties.location_color, argv[i]);
		}
		else
			ft_printf("%sNo such process %s.\33[37m\n",
						dispatch->display.properties.location_color, argv[i]);
		free(pargv[i++]);
	}
}

int					built_jobs(t_dispatch *const dispatch, char **argv)
{
	t_back			*ptr;

	ptr = dispatch->foreground.background.back;
	if (!ptr)
		ft_printf("%sno jobs.\n\33[37m",
				dispatch->display.properties.builtins_color);
	else
	{
		if (*++argv)
			jobs_argv(dispatch, argv);
		else
		{
			while (ptr)
			{
				print_job(dispatch, ptr);
				ptr = ptr->next;
			}
		}
	}
	return (0);
}
