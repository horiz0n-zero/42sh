/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 08:55:45 by afeuerst          #+#    #+#             */
/*   Updated: 2017/11/16 11:05:58 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static char			*g_bonus[] =
{
	"sorted env\n",
	"envguard guard the environ !\n"
	"inibiter using `COMMANDS`\n",
	"subshell using (COMMANDS)\n",
	"list of command using {COMMANDS}\n",
	"redirection on () or {}\n",
	"pipe between () or {} or COMMAND\n",
	"colors builtins, select, show colors\n",
	"job control :\n",
	"background command &\n",
	"fg background to foreground\n",
	"bg commands stopped by ctr-z to background\n",
	"disown : don't manage the specified job\n",
	"stop process (ctr-z)\n",
	"globing\n",
	"auto-completition\n",
	"io redirection <>, herestring : <<< WORLD\n",
	"alias with permanent save\n",
	"pure redirection\n",
	NULL
};

int					built_bonus(t_dispatch *const dispatch, char **argv)
{
	(void)dispatch;
	argv = g_bonus;
	while (*argv)
	{
		write(STDOUT_FILENO, *argv, ft_strlen(*argv));
		argv++;
	}
	return (0);
}
