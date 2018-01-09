/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_percent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 10:26:44 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/14 14:39:09 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static size_t		argv_count(char **const argv)
{
	size_t			i;

	i = 0;
	while (argv[i])
		i++;
	return (i + 1);
}

static void			*only_percent(t_dispatch *const dispatch)
{
	t_back			*ptr;

	ptr = dispatch->foreground.background.back;
	if (ptr)
	{
		while (ptr->next)
			ptr = ptr->next;
		return (SUPER(dispatch)->string.itoa(ptr->pid));
	}
	return (SUPER(dispatch)->string.copy(""));
}

static void			*number_percent(t_dispatch *const dispatch, int n)
{
	t_back			*ptr;

	ptr = dispatch->foreground.background.back;
	if (ptr)
	{
		while (ptr)
		{
			if (!--n)
				return (SUPER(dispatch)->string.itoa(ptr->pid));
			ptr = ptr->next;
		}
	}
	return (SUPER(dispatch)->string.copy(""));
}

static void			*get_percent(t_dispatch *const dispatch, const char *src)
{
	src++;
	if (*src == '%' || !*src)
		return (only_percent(dispatch));
	else
	{
		if (*src >= '0' || *src <= '9')
			return (number_percent(dispatch, string_atoi(src)));
	}
	return (SUPER(dispatch)->string.copy(""));
}

void				*background_percent(t_dispatch *const dispatch, char **argv)
{
	char			**new;
	const size_t	count = argv_count(argv);

	if (!(new = malloc(sizeof(char*) * count)))
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	while (*argv)
	{
		if (**argv == '%')
			*new++ = get_percent(dispatch, *argv);
		else
			*new++ = SUPER(dispatch)->string.copy(*argv);
		argv++;
	}
	*new = NULL;
	return (new - count + 1);
}
