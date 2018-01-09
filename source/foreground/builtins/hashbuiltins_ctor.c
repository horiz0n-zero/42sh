/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashbuiltins_ctor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 14:24:56 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/13 15:27:30 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const t_load_builtins	g_load[] =
{
	{built_env, "env"},
	{built_setenv, "setenv"},
	{built_unsetenv, "unsetenv"},
	{built_cd, "cd"},
	{built_echo, "echo"},
	{built_exit, "exit"},
	{built_exit, "quit"},
	{built_clear, "clear"},
	{built_jobs, "jobs"},
	{built_fg, "fg"},
	{built_bg, "bg"},
	{built_kill, "kill"},
	{built_disown, "disown"},
	{built_alias, "alias"},
	{built_colors, "colors"},
	{built_colors, "color"},
	{built_envguard, "envguard"},
	{built_builtins, "builtins"},
	{built_history, "history"},
	{built_hash, "hash"},
	{built_unset, "unset"},
	{built_export, "export"},
	{built_local, "local"},
	{built_nodename, "nodename"},
	{built_read, "read"},
	{built_bonus, "bonus"}
};

int								built_builtins(t_dispatch *const dispatch,
		char **argv)
{
	static const char			txt[] = "builtins list : \n";
	static const size_t			txt_size = sizeof("builtins list : \n");
	int							i;

	(void)dispatch;
	(void)argv;
	write(STDOUT_FILENO, txt, txt_size);
	i = 0;
	while (i < BUILTINS_COUNT)
		ft_printf("%15s\n", g_load[i++].id);
	return (0);
}

void							ctor_hashbuiltins(t_dispatch *const dispatch)
{
	int							index;

	index = 0;
	dispatch->foreground.builtins.packets =
		malloc(sizeof(t_hashpacket) * BUILTINS_COUNT);
	if (!dispatch->foreground.builtins.packets)
		SUPER(dispatch)->exit(dispatch, REQ_MALLOC);
	dispatch->foreground.builtins.size = BUILTINS_COUNT;
	ft_memset((void*)dispatch->foreground.builtins.packets,
			dispatch->foreground.builtins.size * sizeof(t_hashpacket));
	while (index < BUILTINS_COUNT)
	{
		SUPER(dispatch)->foreground.builtins.append(dispatch,
				g_load[index].id, \
				(void*)g_load[index].func);
		index++;
	}
}
