/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_alias.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 13:53:16 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/01 11:14:08 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void	alias_array_print(const char **src)
{
	while (*src)
		ft_printf("%s ", *src++);
	write(STDOUT_FILENO, "\n", 1);
}

static void			alias_list(t_dispatch *const dispatch)
{
	t_hashpacket	*pos;
	size_t			index;

	index = 0;
	while (index < dispatch->foreground.alias.size)
	{
		pos = dispatch->foreground.alias.packets + index;
		while (pos)
		{
			if (pos->src)
			{
				ft_printf("%s>  %s%s \33[37m",
						dispatch->display.properties.prompt_color,
						dispatch->display.properties.builtins_color, pos->src);
				alias_array_print(pos->element);
			}
			pos = pos->next;
		}
		index++;
	}
}

static void			alias_write(t_dispatch *const dispatch, char **argv)
{
	write(dispatch->foreground.aliasfile, "> ", 2);
	while (*argv)
	{
		write(dispatch->foreground.aliasfile, *argv, ft_strlen(*argv));
		write(dispatch->foreground.aliasfile, " ", 1);
		argv++;
	}
	write(dispatch->foreground.aliasfile, "\n", 1);
}

static void			alias_push_argv(t_dispatch *const dispatch, char **argv)
{
	char **const	alias = argv++;
	size_t			size;
	char			**new;

	size = 0;
	while (argv[size])
		size++;
	if (!(new = malloc(sizeof(char*) * (size + 1))))
		malloc_exit();
	while (*argv)
		*new++ = SUPER(dispatch)->string.copy(*argv++);
	*new = NULL;
	new -= size;
	SUPER(dispatch)->foreground.alias.append(dispatch,
			SUPER(dispatch)->string.copy(*alias), new);
	alias_write(dispatch, alias);
}

int					built_alias(t_dispatch *const dispatch, char **argv)
{
	if (!dispatch->foreground.aliaspath)
	{
		ft_printf("%s alias is not initialized. Nothing done.\33[37m\n",
				dispatch->display.properties.prompt_color);
		return (0);
	}
	if (*++argv && *(argv + 1))
		alias_push_argv(dispatch, argv);
	else
		alias_list(dispatch);
	return (0);
}
