/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   purplegreensh.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstoian <kstoian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:33:21 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/05 13:38:46 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PURPLEGREENSH_H
# define PURPLEGREENSH_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <curses.h>
# include <term.h>
# include <sys/termios.h>
# include <sys/ioctl.h>
# include <sys/utsname.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/mman.h>
# include <stdbool.h>
# include <termios.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <pwd.h>
# include <time.h>
# include "libprintf.h"
# include "properties.h"
# include "utility.h"
# include "execution.h"
# include "history.h"

typedef struct s_dispatch	t_dispatch;
typedef struct s_environ	t_environ;
typedef struct s_display	t_display;
typedef struct s_foreground	t_foreground;
typedef struct s_background	t_background;
typedef struct s_collection	t_collection;
typedef struct s_hashable	t_hashable;
typedef struct s_string		t_string;
typedef struct s_memory		t_memory;
typedef struct s_history	t_history;
typedef struct s_variable	t_variable;

typedef struct s_subclass_dispatch	t_subclass_dispatch;
typedef struct s_subclass_environ	t_subclass_environ;
typedef struct s_class_display		t_class_display;
typedef struct s_subclass_foreground	t_subclass_foreground;
typedef struct s_class_background	t_class_background;
typedef struct s_class_collection	t_class_collection;
typedef struct s_class_hashable		t_class_hashable;
typedef struct s_class_string		t_class_string;
typedef struct s_class_memory		t_class_memory;
typedef struct s_class_history		t_class_history;
typedef struct s_class_variable		t_class_variable;

typedef struct					s_var
{
	char						*key;
	char						*value;
}								t_var;

struct							s_variable
{
	size_t						count;
	size_t						size;
	t_var						*local;
};

struct							s_memory
{
	void						*in;
	const void					*out;
};

struct							s_string
{
	int							random;
	int							pad;
};

typedef struct					s_hashpacket
{
	void						*element;
	char						*src;
	struct s_hashpacket			*next;
}								t_hashpacket;

struct							s_hashable
{
	size_t						size;
	t_hashpacket				*packets;
};

struct							s_history
{
	int							guard;
	int							pad;
	size_t						index;
	t_history_node				*array;
	size_t						size;
	size_t						count;
};

struct							s_collection
{
	t_task						*task;
	t_task						*ctask;
	t_cmd						*ccmd;
};

struct							s_background
{
	pid_t						self_group;
	pid_t						execute;
	pid_t						pipe;
	int							turn;
	pid_t						*pids;
	size_t						pids_count;
	size_t						pids_size;
	t_back						*back;
	const char					**errors;
};

struct							s_foreground
{
	char						*error;
	int							error_required_free;
	int							index;
	t_token						*tokens;
# define TOKENSRC dispatch->foreground.tokens[dispatch->foreground.index].src
# define TOKEN dispatch->foreground.tokens[dispatch->foreground.index]
# define TOKENS(i) dispatch->foreground.tokens[i]

	int							need_task;
	short						mode_pad;
	mode_t						red_mode;
	int							status;
	int							wait;
	t_background				background;
	t_collection				collection;
	t_hashable					binaries;
	t_hashable					builtins;
	t_hashable					alias;
	char						*aliaspath;
	int							aliasfile;
	int							pad;
};

struct							s_display
{
	t_properties				properties;
	t_selection					select;
	struct utsname				node;
	struct termios				current;
	struct termios				saved;
	t_sl						caps[CAP_COUNT];
	char						*buffer;
# define BUFFER(index) dispatch->display.buffer[index]

	size_t						buffer_size;
	size_t						index;
	size_t						indes;
# define DISPLAY(o) SUPER(o)->display
# define INDEXS(x) x->display.indes + x->display.index
# define ISREDGE(o) DISPLAY(o).isredge(INDEXS(o), o->display.co)
# define ISLEDGE(o) DISPLAY(o).isledge(INDEXS(o), o->display.co)
# define CAPS(name) dispatch->display.caps[name]

	size_t						len;
	size_t						co;
	size_t						li;
	int							work;
# define WORKD_MAIN 0
# define WORKD_TXT 1

	int							selection;
	char						*pasteboard;
	int							colors;
	int							stop;
};

struct							s_environ
{
	const void					*pad;
};

struct							s_dispatch
{
	const void					*self;
	char						*base;
	t_environ					env;
	t_variable					var;
	t_display					display;
	t_foreground				foreground;
	t_history					history;
	t_string					string;
	t_memory					memory;
};

# define SUPER(dispatch) ((const t_subclass_dispatch*)(dispatch->self))
# ifdef move
#  undef move
# endif

struct							s_class_variable
{
	void						(*ctor)(t_dispatch *const dispatch);
	void						(*dtor)(t_dispatch *const dispatch);
	int							(*isvar)(register const char *src);
	void						(*append)(t_dispatch *const dispatch,
			const char *src);
	void						(*expand)(t_dispatch *const dispatch);
};
void							ctor_var(t_dispatch *const dispatch);
void							dtor_var(t_dispatch *const dispatch);
int								var_isvar(register const char *src);
void							var_append(t_dispatch *const dispatch,
		const char *src);
void							var_expand(t_dispatch *const dispatch);

struct							s_class_memory
{
	void						(*move)(char *dst, const char *src,
			size_t size);
};
void							memory_move(char *dst, const char *src,
		size_t size);

struct							s_class_string
{
# define COPY(str) string_copy(str)

	void						*(*copy)(const char *src);
	void						*(*ncopy)(const char *src, size_t n);
	void						*(*arraycopy)(const char **src);
	void						(*apush)(char *src, const int index,
			const char c);
	void						(*kpush)(char *src, const int index);
	void						*(*split)(const char *src);
	t_token						*(*toksplit)(register t_dispatch *const
			dispatch);
	size_t						(*toksplit_count)(register t_dispatch *const
			dispatch);
	int							(*atoi)(const char *src);
	char						*(*itoa)(int n);
	char						*(*random)(t_dispatch *const dispatch,
			size_t len, const char *prefix);
	void						(*astrpush)(const char *src, char *dst,
			int index);
	int							(*strinstr)(register const char *in,
			register const char *find);
	void						(*swap)(char *const src);
};
void							*string_copy(const char *src);
void							*string_ncopy(const char *src, size_t n);
void							*string_arraycopy(const char **src);
void							string_apush(char *src, const int index,
		const char c);
void							string_kpush(char *src, const int index);
void							*string_split(const char *src);
t_token							*string_toksplit(register t_dispatch *const
		dispatch);
int								quote_index_value(register t_dispatch *const
	dispatch, t_token *ptr, register int i, int index);
size_t							string_toksplit_count(register t_dispatch *const
		dispatch);
int								string_atoi(const char *src);
char							*string_itoa(int n);
char							*string_stc_itoa(int n);
char							*string_random(t_dispatch *const dispatch,
		size_t len, const char *prefix);
void							string_astrpush(const char *src, char *dst,
		int index);
int								string_strinstr(register const char *in,
		register const char *f);
void							string_swap(char *const src);

struct							s_class_hashable
{
	void						(*ctor)(t_dispatch *const dispatch);
	void						(*dtor)(t_dispatch *const dispatch);
	void						(*append)(t_dispatch *const dispatch, char
			*src, void *const element);
	size_t						(*key)(const char *src);
	void						*(*get)(t_dispatch *const dispatch,
			const char *src);
};
void							ctor_hashablebin(t_dispatch *const dispatch);
void							ctor_hashbuiltins(t_dispatch *const dispatch);
void							ctor_hashalias(t_dispatch *const dispatch);
void							dtor_hashablebin(t_dispatch *const dispatch);
void							dtor_hashbuiltins(t_dispatch *const dispatch);
void							dtor_hashalias(t_dispatch *const dispatch);
void							hashablebin_append(t_dispatch *const dispatch,
		char *src, void *const element);
void							hashbuiltins_append(t_dispatch *const dispatch,
		char *src, void *const element);
void							hashalias_append(t_dispatch *const dispatch,
		char *src, void *const element);
size_t							hashable_key(const char *src);
void							*hashablebin_get(t_dispatch *const dispatch,
		const char *src);
void							*hashbuiltins_get(t_dispatch *const dispatch,
		const char *src);
void							*hashalias_get(t_dispatch *const dispatch,
		const char *src);

struct							s_class_history
{
	void						(*ctor)(t_dispatch *const dispatch);
	void						(*dtor)(t_dispatch *const dispatch);
	void						(*write)(t_dispatch *const dispatch);
	void						(*expand)(t_dispatch *const dispatch);
	void						(*search)(t_dispatch *const dispatch);
};
void							ctor_history(t_dispatch *const dispatch);
void							dtor_history(t_dispatch *const dispatch);
void							history_write(t_dispatch *const dispatch);
void							history_expand(t_dispatch *const dispatch);
void							history_search(t_dispatch *const dispatch);

struct							s_class_collection
{
	void						(*ctor)(t_dispatch *const dispatch);
	void						(*dtor)(t_dispatch *const dispatch);
	void						(*append)(t_dispatch *const dispatch,
			t_task *const task);
	void						(*append_cmd)(t_dispatch *const dispatch,
			t_cmd *cmd);
};
void							ctor_collection(t_dispatch *const dispatch);
void							dtor_collection(t_dispatch *const dispatch);
void							collection_append(t_dispatch *const dispatch,
		t_task *const task);
void							collection_append_cmd(t_dispatch *const
		dispatch, t_cmd *cmd);

struct							s_class_background
{
	void						(*ctor)(t_dispatch *const dispatch);
	void						(*dtor)(t_dispatch *const dispatch);
	void						(*append_pid)(t_dispatch *const dispatch,
			const pid_t pid);
	void						(*wait_pids)(t_dispatch *const dispatch);
	void						*(*percent)(t_dispatch *const dispatch,
			char **argv);
	void						(*append)(t_dispatch *const dispatch,
			t_cmd *const cmd, const int status);
	t_back						*(*get)(t_dispatch *const dispatch,
			const pid_t pid);
	void						(*remove)(t_dispatch *const dispatch,
			const pid_t pid);
};
void							ctor_background(t_dispatch *const dispatch);
void							dtor_background(t_dispatch *const dispatch);
void							background_append_pid(
		t_dispatch *const dispatch, const pid_t pid);
void							background_wait_pids(
		t_dispatch *const dispatch);
void							*background_percent(t_dispatch *const dispatch,
		char **argv);
void							background_append(t_dispatch *const dispatch,
		t_cmd *const cmd, const int status);
t_back							*background_get(t_dispatch *const dispatch,
		const pid_t pid);
void							background_remove(t_dispatch *const dispatch,
		const pid_t pid);

struct							s_subclass_foreground
{
	void						(*ctor)(t_dispatch *const dispatch);
	void						(*dtor)(t_dispatch *const dispatch);
	void						(*setsignal)(const int type);
# define DEFAULT 0
# define IGNORE 1
# define SELF 2

	void						(*get)(t_dispatch *const dispatch);
	void						(*noget)(t_dispatch *const dispatch);
	void						(*get_exec)(t_dispatch *const dispatch);
	void						(*get_argv)(t_dispatch *const dispatch,
			size_t count);
	void						(*get_subshell)(t_dispatch *const dispatch);
	void						(*get_inibit)(t_dispatch *const dispatch,
			t_token *new);
	void						(*get_shell)(t_dispatch *const dispatch);
	void						(*redirections)(t_dispatch *const dispatch);
	void						(*task_redirections)(
			t_dispatch *const dispatch);
	void						(*perfom)(t_dispatch *const dispatch);
	void						(*set_std)(t_task *const task,
			t_cmd *const cmd);
	void						(*set_red)(t_dispatch *const dispatch,
			t_cmd *const cmd);
	int							(*checkstatus)(t_dispatch *const dispatch,
			t_cmd *const cmd);
	void						(*execute)(t_dispatch *const dispatch);
	void						*(*pipexec)(t_dispatch *const dispatch,
			t_task *const task, t_cmd *cmd);
	void						*(*taskpipexec)(t_dispatch *const dispatch,
			t_task *task);
	void						(*destroy)(t_dispatch *const dispatch);
	void						*(*globing)(char *const src, size_t *const n);
	void						(*history)(t_dispatch *const dispatch);
	t_class_background			background;
	t_class_collection			collection;
	t_class_hashable			binaries;
	t_class_hashable			builtins;
	t_class_hashable			alias;
# ifdef ERROR
#  undef ERROR
# endif
# define ERROR dispatch->foreground.error
# ifdef FINDEX
#  undef FINDEX
# endif
# define FINDEX dispatch->foreground.index
# define CHOUETTE (const void*)(ptr + sizeof(t_color_header))

};
void							ctor_foreground(t_dispatch *const dispatch);
void							dtor_foreground(t_dispatch *const dispatch);
void							foreground_setsignal(const int type);
void							signal_exit(int signal);
void							signal_window(int signal);
void							signal_child(int signal);
void							foreground_get(t_dispatch *const dispatch);
void							foreground_noget(t_dispatch *const dispatch);
void							foreground_get_exec(t_dispatch *const dispatch);
void							foreground_get_argv(t_dispatch *const dispatch,
		size_t count);
void							foreground_get_subshell(
		t_dispatch *const dispatch);
void							foreground_get_inibit(
		t_dispatch *const dispatch, t_token *new);
void							foreground_get_shell(
		t_dispatch *const dispatch);
void							foreground_redirections(
		t_dispatch *const dispatch);
void							foreground_task_redirections(
		t_dispatch *const dispatch);
void							foreground_perfom(t_dispatch *const dispatch);
void							foreground_set_std(t_task *const task,
		t_cmd *const cmd);
void							foreground_set_std_task(t_task *const task);
void							foreground_set_red(t_dispatch *const dispatch,
		t_cmd *const cmd);
int								foreground_checkstatus(
		t_dispatch *const dispatch, t_cmd *const cmd);
void							foreground_execute(t_dispatch *const dispatch);
void							*foreground_pipexec(t_dispatch *const dispatch,
		t_task *const task, t_cmd *cmd);
void							*foreground_taskpipexec(
		t_dispatch *const dispatch, t_task *task);
void							foreground_destroy(t_dispatch *const dispatch);
void							*foreground_globing(char *const src,
		size_t *const n);
void							foreground_history(t_dispatch *const dispatch);

struct							s_class_display
{
	void						(*ctor)(t_dispatch *const dispatch);
	void						(*dtor)(t_dispatch *const dispatch);
	void						(*read_one)(const char *ptr,
			t_dispatch *const dispatch);
	void						(*read_three)(const char *ptr,
			t_dispatch *const dispatch);
	void						(*read_more)(const char *ptr,
			t_dispatch *const dispatch);
	void						(*prompt)(const char *pr, const size_t indes,
			t_dispatch *const dispatch);
	void						(*tmp_loop)(t_dispatch *const dispatch);
	void						(*tmp_breakloop)(t_dispatch *const dispatch);
	void						(*here_loop)(t_dispatch *const dispatch,
			int *const stop);
	void						(*expand)(t_dispatch *const dispatch);
	void						(*getctxt)(t_dispatch *const dispatch,
			const char c);
	void						(*gettxt)(t_dispatch *const dispatch,
			const char *const src);
	void						(*getstring)(t_dispatch *const dispatch,
			const char *str);
	void						(*select)(t_dispatch *const dispatch);
	void						(*selection)(t_dispatch *const dispatch);
	void						(*selected)(t_dispatch *const dispatch);
	void						(*select_print)(t_dispatch *const dispatch);
	void						(*autoselect)(t_dispatch *const dispatch,
			char *const backworld);
	void						(*cancel)(t_dispatch *const dispatch);
	void						(*lclear)(t_dispatch *const dispatch);
	int							(*isredge)(const size_t n, const size_t of);
	int							(*isledge)(const size_t n, const size_t of);
	void						(*start_line)(t_dispatch *const dispatch);
	void						(*end_line)(t_dispatch *const dispatch);
	void						(*goposition)(const size_t pos,
			t_dispatch *const dispatch);
	void						(*append)(const char c,
			t_dispatch *const dispatch);
	void						(*remove)(t_dispatch *const dispatch);
	void						(*delete)(t_dispatch *const dispatch);
	void						(*right)(t_dispatch *const dispatch);
	void						(*left)(t_dispatch *const dispatch);
	void						(*word_left)(t_dispatch *const dispatch);
	void						(*word_right)(t_dispatch *const dispatch);
	void						(*up)(t_dispatch *const dispatch);
	void						(*down)(t_dispatch *const dispatch);
	void						(*line_up)(t_dispatch *const dispatch);
	void						(*line_down)(t_dispatch *const dispatch);
	void						(*home)(t_dispatch *const dispatch);
	void						(*end)(t_dispatch *const dispatch);
	void						(*copy)(t_dispatch *const dispatch);
	void						(*paste)(t_dispatch *const dispatch);
	void						(*writecolor)(t_dispatch *const dispatch);
	void						(*readcolor)(t_dispatch *const dispatch);
};

void							ctor_display(t_dispatch *const dispatch);
void							dtor_display(t_dispatch *const dispatch);
void							display_read_one(const char *ptr,
		t_dispatch *const dispatch);
void							display_read_three(const char *ptr,
		t_dispatch *const dispatch);
void							display_read_more(const char *ptr,
		t_dispatch *const dispatch);
void							display_prompt(const char *pr,
		const size_t indes, t_dispatch *const dispatch);
void							display_tmp_loop(t_dispatch *const dispatch);
void							display_tmp_breakloop(
		t_dispatch *const dispatch);
void							display_here_loop(t_dispatch *const dispatch,
		int *const stop);
void							display_expand(t_dispatch *const dispatch);
void							display_getctxt(t_dispatch *const dispatch,
		const char c);
void							display_gettxt(t_dispatch *const dispatch,
		const char *const src);
void							display_getstring(t_dispatch *const dispatch,
		const char *str);
void							display_select(t_dispatch *const dispatch);
void							display_selection(t_dispatch *const dispatch);
void							open_append(const char *const path, t_select
		*select, t_selection *const selection, t_dispatch *const dispatch);
void							display_selected(t_dispatch *const dispatch);
void							display_select_print(
		t_dispatch *const dispatch);
void							display_autoselect(t_dispatch *const dispatch,
		char *const backworld);
void							search_world_append(const char *const world,
		t_select *select, t_selection *const selection,
		t_dispatch *const dispatch);
void							display_cancel(t_dispatch *const dispatch);
void							display_lclear(t_dispatch *const dispatch);
int								display_isredge(
		const size_t n, const size_t of);
int								display_isledge(
		const size_t n, const size_t of);
void							display_start_line(t_dispatch *const dispatch);
void							display_end_line(t_dispatch *const dispatch);
void							display_goposition(const size_t pos,
		t_dispatch *const dispatch);
void							display_append(const char c,
		t_dispatch *const dispatch);
void							display_remove(t_dispatch *const dispatch);
void							display_delete(t_dispatch *const dispatch);
void							display_left(t_dispatch *const dispatch);
void							display_right(t_dispatch *const dispatch);
void							display_word_left(t_dispatch *const dispatch);
void							display_word_right(t_dispatch *const dispatch);
void							display_up(t_dispatch *const dispatch);
void							display_down(t_dispatch *const dispatch);
void							display_line_up(t_dispatch *const dispatch);
void							display_line_down(t_dispatch *const dispatch);
void							display_home(t_dispatch *const dispatch);
void							display_end(t_dispatch *const dispatch);
void							display_copy(t_dispatch *const dispatch);
void							display_paste(t_dispatch *const dispatch);
void							display_writecolor(t_dispatch *const dispatch);
void							display_readcolor(t_dispatch *const dispatch);

typedef void					(*t_readfunc)(const char *ptr,
		t_dispatch *const dispatch);

struct							s_subclass_environ
{
	void						(*ctor)(t_dispatch *const dispatch);
	void						(*dtor)(t_dispatch *const dispatch);
	size_t						(*count)(void);
	void						*(*get)(t_dispatch *const dispatch,
			const char *name);
# define ENVGET(str) SUPER(dispatch)->env.get(dispatch, str)

	void						(*remove)(t_dispatch *const dispatch,
			const char *const name);
	void						(*guard)(t_dispatch *const dispatch);
	void						(*append)(t_dispatch *const dispatch,
			const char *name, const char *value);
	int							(*corres)(const char *name, const char *env);
	void						(*sort)(const int count, char **array);
};
void							ctor_environ(t_dispatch *const dispatch);
void							dtor_environ(t_dispatch *const dispatch);
size_t							environ_count(void);
void							*environ_get(t_dispatch *const dispatch,
		const char *name);
void							environ_remove(t_dispatch *const dispatch,
		const char *const src);
void							environ_guard(t_dispatch *const dispatch);
void							environ_append(t_dispatch *const dispatch,
		const char *name, const char *value);
int								environ_corres(const char *name,
		const char *env);
void							environ_shell_sort(const int count,
		char **array);

struct							s_subclass_dispatch
{
	void						(*ctor)(t_dispatch *const dispatch,
			const void *const self);
	void						(*dtor)(t_dispatch *const dispatch);
	void						(*exit)(t_dispatch *const dispatch,
			const char *err);
	void						(*start)(t_dispatch *const dispatch);
	void						(*sleep)(const time_t secs, const long nsecs);
	t_subclass_environ			env;
	t_class_variable			var;
	t_class_display				display;
	t_subclass_foreground		foreground;
	t_class_history				history;
	t_class_string				string;
	t_class_memory				memory;
};
void							ctor_dispatch(t_dispatch *const dispatch,
		const void *const self);
void							dtor_dispatch(t_dispatch *const dispatch);
void							dispatch_exit(t_dispatch *const dispatch,
		const char *err);
void							dispatch_start(t_dispatch *const dispatch);
void							dispatch_sleep(const time_t secs,
		const long nsecs);
void							*get_dispatch(void *const dispatch);

typedef struct					s_guard
{
	const char					*name;
	char						*(*get)(t_dispatch *const dispatch);
	char						*default_name;
}								t_guard;
char							*environ_pwd(t_dispatch *const dispatch);
char							*environ_home(t_dispatch *const dispatch);

typedef int						(*t_builtfunc)(t_dispatch *const dispatch,
		char **argv);
int								built_env(t_dispatch *const dispatch,
		char **argv);
int								built_unsetenv(t_dispatch *const dispatch,
		char **argv);
int								built_setenv(t_dispatch *const dispatch,
		char **argv);
int								built_cd(t_dispatch *const dispatch,
		char **argv);
int								built_echo(t_dispatch *const dispatch,
		char **argv);
int								built_exit(t_dispatch *const dispatch,
		char **argv);
int								built_clear(t_dispatch *const dispatch,
		char **argv);
int								built_jobs(t_dispatch *const dispatch,
		char **argv);
int								built_fg(t_dispatch *const dispatch,
		char **argv);
int								built_bg(t_dispatch *const dispatch,
		char **argv);
int								built_disown(t_dispatch *const dispatch,
		char **argv);
int								built_alias(t_dispatch *const dispatch,
		char **argv);
int								built_colors(t_dispatch *const dispatch,
		char **argv);
int								built_builtins(t_dispatch *const dispatch,
		char **argv);
int								built_kill(t_dispatch *const dispatch,
		char **argv);
int								built_envguard(t_dispatch *const dispatch,
		char **argv);
int								built_history(t_dispatch *const dispatch,
		char **argv);
int								built_bonus(t_dispatch *const dispatch,
		char **argv);
int								built_hash(t_dispatch *const dispatch,
		char **argv);
int								built_unset(t_dispatch *const dispatch,
		char **argv);
int								built_export(t_dispatch *const dispatch,
		char **argv);
int								built_local(t_dispatch *const dispatch,
		char **argv);
int								built_nodename(t_dispatch *const dispatch,
		char **argv);
int								built_read(t_dispatch *const dispatch,
		char **argv);

# define BUILTINS_COUNT 26

typedef struct					s_load_builtins
{
	t_builtfunc					func;
	char						*id;
}								t_load_builtins;

typedef void					(*t_redfunc)(t_dispatch *const dispatch,
		int def);
void							red_r(t_dispatch *const dispatch, int def);
void							red_rr(t_dispatch *const dispatch, int def);
void							red_l(t_dispatch *const dispatch, int def);
void							red_ll(t_dispatch *const dispatch, int def);
void							red_lll(t_dispatch *const dispatch, int def);
void							red_ar(t_dispatch *const dispatch, int def);
void							red_la(t_dispatch *const dispatch, int def);
void							red_io(t_dispatch *const dispatch, int def);
void							tred_r(t_dispatch *const dispatch, int def);
void							tred_rr(t_dispatch *const dispatch, int def);
void							tred_l(t_dispatch *const dispatch, int def);
void							tred_ll(t_dispatch *const dispatch, int def);
void							tred_lll(t_dispatch *const dispatch, int def);
void							tred_ar(t_dispatch *const dispatch, int def);
void							tred_la(t_dispatch *const dispatch, int def);
void							tred_io(t_dispatch *const dispatch, int def);

typedef size_t					(*t_perf_len)(t_dispatch *const dispatch,
		char **src);
typedef void					*(*t_perf_push)(t_dispatch *const dispatch,
		char **src, char *dst);

size_t							dollar_len(t_dispatch *const dispatch,
		char **src);
void							*dollar_push(t_dispatch *const dispatch,
		char **src, char *dst);
size_t							home_len(t_dispatch *const dispatch,
		char **src);
void							*home_push(t_dispatch *const dispatch,
		char **src, char *dst);

typedef struct					s_perfom
{
	size_t						index;
	t_perf_len					func_len;
	t_perf_push					func_push;
}								t_perfom;

typedef void					(*t_exec_task)(t_dispatch *const dispatch,
								t_task *const task);

typedef void					(*t_execute)(t_dispatch *const dispatch,
								t_task *const task, t_cmd *const cmd);

void							exec_pure(t_dispatch *const dispatch,
								t_task *const task, t_cmd *const cmd);

void							exec_red(t_dispatch *const dispatch,
								t_task *const task, t_cmd *const cmd);

void							exec_built(t_dispatch *const dispatch,
								t_task *const task, t_cmd *const cmd);

void							*colors_select(t_dispatch *const dispatch);

#endif
