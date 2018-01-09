/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   purplegreensh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:33:54 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/05 13:38:55 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static const t_subclass_dispatch		g_desc_dispatch =
{
	ctor_dispatch,
	dtor_dispatch,
	dispatch_exit,
	dispatch_start,
	dispatch_sleep,
	{
		ctor_environ,
		dtor_environ,
		environ_count,
		environ_get,
		environ_remove,
		environ_guard,
		environ_append,
		environ_corres,
		environ_shell_sort
	},
	{
		ctor_var,
		dtor_var,
		var_isvar,
		var_append,
		var_expand
	},
	{
		ctor_display,
		dtor_display,
		display_read_one,
		display_read_three,
		display_read_more,
		display_prompt,
		display_tmp_loop,
		display_tmp_breakloop,
		display_here_loop,
		display_expand,
		display_getctxt,
		display_gettxt,
		display_getstring,
		display_select,
		display_selection,
		display_selected,
		display_select_print,
		display_autoselect,
		display_cancel,
		display_lclear,
		display_isredge,
		display_isledge,
		display_start_line,
		display_end_line,
		display_goposition,
		display_append,
		display_remove,
		display_delete,
		display_right,
		display_left,
		display_word_right,
		display_word_left,
		display_up,
		display_down,
		display_line_up,
		display_line_down,
		display_home,
		display_end,
		display_copy,
		display_paste,
		display_writecolor,
		display_readcolor
	},
	{
		ctor_foreground,
		dtor_foreground,
		foreground_setsignal,
		foreground_get,
		foreground_noget,
		foreground_get_exec,
		foreground_get_argv,
		foreground_get_subshell,
		foreground_get_inibit,
		foreground_get_shell,
		foreground_redirections,
		foreground_task_redirections,
		foreground_perfom,
		foreground_set_std,
		foreground_set_red,
		foreground_checkstatus,
		foreground_execute,
		foreground_pipexec,
		foreground_taskpipexec,
		foreground_destroy,
		foreground_globing,
		foreground_history,
		{
			ctor_background,
			dtor_background,
			background_append_pid,
			background_wait_pids,
			background_percent,
			background_append,
			background_get,
			background_remove
		},
		{
			ctor_collection,
			dtor_collection,
			collection_append,
			collection_append_cmd
		},
		{
			ctor_hashablebin,
			dtor_hashablebin,
			hashablebin_append,
			hashable_key,
			hashablebin_get
		},
		{
			ctor_hashbuiltins,
			dtor_hashbuiltins,
			hashbuiltins_append,
			hashable_key,
			hashbuiltins_get
		},
		{
			ctor_hashalias,
			dtor_hashalias,
			hashalias_append,
			hashable_key,
			hashalias_get
		}
	},
	{
		ctor_history,
		dtor_history,
		history_write,
		history_expand,
		history_search
	},
	{
		string_copy,
		string_ncopy,
		string_arraycopy,
		string_apush,
		string_kpush,
		string_split,
		string_toksplit,
		string_toksplit_count,
		string_atoi,
		string_itoa,
		string_random,
		string_astrpush,
		string_strinstr,
		string_swap
	},
	{
		memory_move
	}
};

static const t_readfunc					g_reads[] =
{
	display_read_one,
	display_read_one,
	display_read_more,
	display_read_three,
	display_read_more,
	display_read_more,
	display_read_more,
	display_read_more,
	display_read_more
};

static void								shstart(t_dispatch *const dispatch)
{
	static int64_t						data;
	static char *const					ptr = (void*)&data;
	ssize_t								size;

	while (true)
	{
		size = read(STDIN_FILENO, ptr, sizeof(int64_t));
		g_reads[size](ptr, dispatch);
	}
}

int										main(void)
{
	t_dispatch							dispatch;

	g_desc_dispatch.ctor(&dispatch, &g_desc_dispatch);
	get_dispatch(&dispatch);
	shstart(&dispatch);
}
