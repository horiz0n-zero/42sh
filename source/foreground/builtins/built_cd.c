/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 13:30:50 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/17 09:47:22 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static void				cd_home(t_dispatch *const dispatch)
{
	char *const			home = SUPER(dispatch)->env.get(dispatch, "HOME");
	static const char	jojo[] = "$HOME doesn't set.\n";
	static const size_t	jojo_size = sizeof(jojo);
	static const char	juju[] = "Bad $HOME\n";
	static const size_t	juju_size = sizeof(juju);

	if (!home)
	{
		write(STDOUT_FILENO, jojo, jojo_size);
		return ;
	}
	if (chdir(home))
	{
		write(STDOUT_FILENO, juju, juju_size);
		return ;
	}
	SUPER(dispatch)->env.append(dispatch, "OLDPWD",
			SUPER(dispatch)->env.get(dispatch, "PWD"));
	SUPER(dispatch)->env.append(dispatch, "PWD", home);
}

static void				cd_minus(t_dispatch *const dispatch)
{
	char				*dest;

	dest = SUPER(dispatch)->env.get(dispatch, "OLDPWD");
	if (chdir(dest))
		ft_printf(RED_OPENF, dest);
	dest = SUPER(dispatch)->string.copy(dest);
	SUPER(dispatch)->env.append(dispatch, "OLDPWD",
			SUPER(dispatch)->env.get(dispatch, "PWD"));
	SUPER(dispatch)->env.append(dispatch, "PWD", dest);
	free(dest);
}

static void				cd_go(t_dispatch *const dispatch, const char *path)
{
	static char			buffer[2024];

	if (chdir(path))
	{
		ft_printf(RED_OPENF, path);
		return ;
	}
	getcwd(buffer, 2024);
	SUPER(dispatch)->env.append(dispatch, "OLDPWD",
			SUPER(dispatch)->env.get(dispatch, "PWD"));
	SUPER(dispatch)->env.append(dispatch, "PWD", buffer);
}

int						built_cd(t_dispatch *const dispatch, char **argv)
{
	SUPER(dispatch)->env.guard(dispatch);
	if (*++argv)
	{
		if (**argv == '-' && !*(*argv + 1))
			cd_minus(dispatch);
		else
			cd_go(dispatch, *argv);
	}
	else
		cd_home(dispatch);
	return (0);
}
