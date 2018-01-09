# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kstoian <kstoian@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/17 12:12:28 by afeuerst          #+#    #+#              #
#    Updated: 2018/01/05 15:09:50 by afeuerst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

NAME = 42sh

INCLUDE = -I ./includes -I ./functions/ft_printf/includes

FLAGS = -Wall -Wextra -Werror

C_SRC = ./functions/ft_printf/srcs/core/lenght/lenght_hexa.c \
		./functions/ft_printf/srcs/core/lenght/lenght_int.c \
		./functions/ft_printf/srcs/core/lenght/lenght_int_long.c \
		./functions/ft_printf/srcs/core/lenght/lenght_octal.c \
		./functions/ft_printf/srcs/core/lenght/lenght_octal_long.c \
		./functions/ft_printf/srcs/core/lenght/lenght_percent.c \
		./functions/ft_printf/srcs/core/lenght/lenght_pointer.c \
		./functions/ft_printf/srcs/core/lenght/lenght_string.c \
		./functions/ft_printf/srcs/core/lenght/lenght_uint.c \
		./functions/ft_printf/srcs/core/lenght/lenght_uint_long.c \
		./functions/ft_printf/srcs/core/lenght/lenght_unicode.c \
		./functions/ft_printf/srcs/core/lenght/lenght_unicode_string.c \
		./functions/ft_printf/srcs/core/lenght/lenght_void.c \
		./functions/ft_printf/srcs/core/printf_exec.c \
		./functions/ft_printf/srcs/core/printf_get_data.c \
		./functions/ft_printf/srcs/core/transform/transform_char.c \
		./functions/ft_printf/srcs/core/transform/transform_hexa_lower.c \
		./functions/ft_printf/srcs/core/transform/transform_hexa_upper.c \
		./functions/ft_printf/srcs/core/transform/transform_int.c \
		./functions/ft_printf/srcs/core/transform/transform_octal.c \
		./functions/ft_printf/srcs/core/transform/transform_percent.c \
		./functions/ft_printf/srcs/core/transform/transform_pointer.c \
		./functions/ft_printf/srcs/core/transform/transform_string.c \
		./functions/ft_printf/srcs/core/transform/transform_uint.c \
		./functions/ft_printf/srcs/core/transform/transform_unicode.c \
		./functions/ft_printf/srcs/core/transform/transform_unicode_string.c \
		./functions/ft_printf/srcs/core/transform/transform_void.c \
		./functions/ft_printf/srcs/core/utility/print_atoi.c \
		./functions/ft_printf/srcs/ft_fprintf.c \
		./functions/ft_printf/srcs/ft_printf.c \
		./functions/ft_printf/srcs/ft_vasprintf.c \
		./source/background/background_append.c \
		./source/background/background_append_pid.c \
		./source/background/background_get.c \
		./source/background/background_percent.c \
		./source/background/background_remove.c \
		./source/background/background_wait_pids.c \
		./source/background/ctor_background.c \
		./source/background/dtor_background.c \
		./source/collection/collection_append.c \
		./source/collection/ctor_collection.c \
		./source/collection/dtor_collection.c \
		./source/dispatch/ctor_dispatch.c \
		./source/dispatch/dispatch_exit.c \
		./source/dispatch/dispatch_sleep.c \
		./source/dispatch/dispatch_start.c \
		./source/dispatch/dtor_dispatch.c \
		./source/display/ctor_display.c \
		./source/display/display_autoselect.c \
		./source/display/display_autoselect_append.c \
		./source/display/display_cancel.c \
		./source/display/display_clear.c \
		./source/display/display_end_line.c \
		./source/display/display_expand.c \
		./source/display/display_getsplit.c \
		./source/display/display_getstring.c \
		./source/display/display_goposition.c \
		./source/display/display_here_loop.c \
		./source/display/display_isat.c \
		./source/display/display_keyboard_cut_paste.c \
		./source/display/display_keyboard_delete.c \
		./source/display/display_keyboard_home_end.c \
		./source/display/display_keyboard_insert.c \
		./source/display/display_keyboard_remove.c \
		./source/display/display_keyboard_right_left.c \
		./source/display/display_keyboard_up_down.c \
		./source/display/display_prompt.c \
		./source/display/display_read_more.c \
		./source/display/display_read_one.c \
		./source/display/display_read_three.c \
		./source/display/display_readcolor.c \
		./source/display/display_select.c \
		./source/display/display_select_print.c \
		./source/display/display_selected.c \
		./source/display/display_selection.c \
		./source/display/display_selection_append.c \
		./source/display/display_start_line.c \
		./source/display/display_tmp_breakloop.c \
		./source/display/display_tmp_loop.c \
		./source/display/display_writecolor.c \
		./source/display/dtor_display.c \
		./source/environ/ctor_environ.c \
		./source/environ/dtor_environ.c \
		./source/environ/environ_append.c \
		./source/environ/environ_corres.c \
		./source/environ/environ_count.c \
		./source/environ/environ_get.c \
		./source/environ/environ_guard.c \
		./source/environ/environ_home.c \
		./source/environ/environ_pwd.c \
		./source/environ/environ_remove.c \
		./source/environ/environ_shell_sort.c \
		./source/foreground/builtins/built_alias.c \
		./source/foreground/builtins/built_bg.c \
		./source/foreground/builtins/built_bonus.c \
		./source/foreground/builtins/built_cd.c \
		./source/foreground/builtins/built_clear.c \
		./source/foreground/builtins/built_colors.c \
		./source/foreground/builtins/built_disown.c \
		./source/foreground/builtins/built_echo.c \
		./source/foreground/builtins/built_env.c \
		./source/foreground/builtins/built_envguard.c \
		./source/foreground/builtins/built_exit.c \
		./source/foreground/builtins/built_export.c \
		./source/foreground/builtins/built_fg.c \
		./source/foreground/builtins/built_hash.c \
		./source/foreground/builtins/built_history.c \
		./source/foreground/builtins/built_jobs.c \
		./source/foreground/builtins/built_kill.c \
		./source/foreground/builtins/built_local.c \
		./source/foreground/builtins/built_nodename.c \
		./source/foreground/builtins/built_read.c \
		./source/foreground/builtins/built_setenv.c \
		./source/foreground/builtins/built_unset.c \
		./source/foreground/builtins/built_unsetenv.c \
		./source/foreground/builtins/colors/colors_select.c \
		./source/foreground/builtins/hashalias_append.c \
		./source/foreground/builtins/hashalias_ctor.c \
		./source/foreground/builtins/hashalias_dtor.c \
		./source/foreground/builtins/hashalias_get.c \
		./source/foreground/builtins/hashbuiltins_append.c \
		./source/foreground/builtins/hashbuiltins_ctor.c \
		./source/foreground/builtins/hashbuiltins_dtor.c \
		./source/foreground/builtins/hashbuiltins_get.c \
		./source/foreground/builtins/history/histo_caw.c \
		./source/foreground/builtins/history/histo_d.c \
		./source/foreground/ctor_foreground.c \
		./source/foreground/dtor_foreground.c \
		./source/foreground/exec/exec_built.c \
		./source/foreground/exec/exec_pure.c \
		./source/foreground/exec/exec_red.c \
		./source/foreground/exec/new_cmd.c \
		./source/foreground/exec/new_red.c \
		./source/foreground/exec/new_task.c \
		./source/foreground/foreground_checkstatus.c \
		./source/foreground/foreground_destroy.c \
		./source/foreground/foreground_execute.c \
		./source/foreground/foreground_get.c \
		./source/foreground/foreground_get_argv.c \
		./source/foreground/foreground_get_exec.c \
		./source/foreground/foreground_get_inibit.c \
		./source/foreground/foreground_get_shell.c \
		./source/foreground/foreground_get_subshell.c \
		./source/foreground/foreground_history.c \
		./source/foreground/foreground_perfom.c \
		./source/foreground/foreground_pipexec.c \
		./source/foreground/foreground_redirections.c \
		./source/foreground/foreground_set_red.c \
		./source/foreground/foreground_set_std.c \
		./source/foreground/foreground_set_std_task.c \
		./source/foreground/foreground_setsignal.c \
		./source/foreground/foreground_task_redirections.c \
		./source/foreground/foreground_taskpipexec.c \
		./source/foreground/globing/foreground_globing.c \
		./source/foreground/globing/ismatching.c \
		./source/foreground/hashbinaries/ctor_hashablebin.c \
		./source/foreground/hashbinaries/dtor_hashablebin.c \
		./source/foreground/hashbinaries/hashable_append.c \
		./source/foreground/hashbinaries/hashable_get.c \
		./source/foreground/hashbinaries/hashable_key.c \
		./source/foreground/perfom/dollar.c \
		./source/foreground/perfom/home.c \
		./source/foreground/redirection/red_and.c \
		./source/foreground/redirection/red_heredoc.c \
		./source/foreground/redirection/red_herestring.c \
		./source/foreground/signal_child.c \
		./source/foreground/signal_exit.c \
		./source/foreground/signal_window.c \
		./source/history/ctor_history.c \
		./source/history/dtor_history.c \
		./source/history/history_expand.c \
		./source/history/history_search.c \
		./source/history/history_write.c \
		./source/memory/memory_move.c \
		./source/purplegreensh.c \
		./source/string/string_apush.c \
		./source/string/string_arraycopy.c \
		./source/string/string_astrpush.c \
		./source/string/string_atoi.c \
		./source/string/string_copy.c \
		./source/string/string_itoa.c \
		./source/string/string_kpush.c \
		./source/string/string_ncopy.c \
		./source/string/string_random.c \
		./source/string/string_split.c \
		./source/string/string_strinstr.c \
		./source/string/string_swap.c \
		./source/string/string_toksplit.c \
		./source/string/string_toksplit_count.c \
		./source/string/toktype_common.c \
		./source/string/toktype_quote.c \
		./source/string/toktype_sep.c \
		./source/utility/ft_ismultipleof.c \
		./source/utility/ft_memset.c \
		./source/utility/ft_stccjoin.c \
		./source/utility/ft_strcjoin.c \
		./source/utility/ft_strcmp.c \
		./source/utility/ft_strjoin.c \
		./source/utility/ft_strlen.c \
		./source/utility/get_dispatch.c \
		./source/utility/isoftype.c \
		./source/utility/karray.c \
		./source/utility/ktoken.c \
		./source/utility/malloc_exit.c \
		./source/utility/tokenscopy.c \
		./source/utility/tokensinsert.c \
		./source/variable/ctor_var.c \
		./source/variable/dtor_var.c \
		./source/variable/var_append.c \
		./source/variable/var_expand.c \
		./source/variable/var_isvar.c \
		./source/utility/force_stop.c

LIB = ./functions/ft_printf/libftprintf.a -ltermcap

all: $(NAME)

$(NAME): $(C_SRC)
	@make -j -C functions/ft_printf
	@printf "\e[38;05;208mCompiling %s ..." $(NAME)
	@clang $(LIB) $(FLAGS) $(INCLUDE) $(C_SRC) -o $(NAME)
	@printf "\r\e[38;05;118m%s is now compiled !\n" $(NAME)

clean:
	@make clean -C functions/ft_printf
	@printf "\e[35m"

fclean: clean
	@make fclean -C functions/ft_printf
	@printf "\33[38;05;196m%s as been removed.\n" $(NAME)
	@rm -rf $(NAME)

re: fclean all
