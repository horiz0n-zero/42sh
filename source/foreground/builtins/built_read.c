/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:27:40 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 14:37:15 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static char		**flag(char **args, int *c)
{
	size_t		i;

	i = 0;
	*c = 0;
	while (args != NULL && *args && args[0][0] == '-')
	{
		while (args[0][i] != '\0')
		{
			if (args[0][i] == 'r')
				*c = 1;
			i++;
		}
		i = 0;
		args++;
	}
	return (args);
}

static char		*joiner(char *src, char *rest)
{
	char		*ret;

	ret = ft_strjoin(src, rest);
	free(src);
	return (ret);
}

static char		*readerr(t_dispatch *const dispatch)
{
	ssize_t		i;
	char		buff[4096];

	i = 0;
	if ((i = read(STDIN_FILENO, buff, 4096)) > 1)
	{
		buff[i - 1] = '\0';
		return (SUPER(dispatch)->string.copy(buff));
	}
	return (NULL);
}

static char		*reader(t_dispatch *const dispatch, char *tmp, ssize_t i)
{
	char		buff[4096];

	while ((i = read(STDIN_FILENO, buff, 4096)))
	{
		if (i > 1 && buff[i - 2] != '\\')
		{
			buff[i - 1] = '\0';
			if (tmp)
				tmp = joiner(tmp, buff);
			else
				tmp = SUPER(dispatch)->string.copy(buff);
			break ;
		}
		if (i < 1 || *buff == '\n')
			break ;
		if (i > 1 && buff[i - 2] == '\\')
			buff[i - 2] = '\0';
		if (tmp && buff[0])
			tmp = joiner(tmp, buff);
		else if (buff[0])
			tmp = SUPER(dispatch)->string.copy(buff);
	}
	return (tmp);
}

int				built_read(t_dispatch *const dispatch, char **argv)
{
	int			c;
	char		**args;
	char		*buff;
	char		*tmp;

	tmp = NULL;
	args = flag(argv + 1, &c);
	buff = c ? readerr(dispatch) : reader(dispatch, tmp, 0);
	if (*args && buff)
	{
		SUPER(dispatch)->var.append(dispatch,
				(tmp = ft_strcjoin(*args, buff, '=')));
		args++;
		free(tmp);
	}
	if (buff)
		free(buff);
	while (*args)
	{
		SUPER(dispatch)->var.append(dispatch, ft_stcjoin(*args, "="));
		args++;
	}
	return (0);
}
