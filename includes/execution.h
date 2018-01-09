/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:32:35 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 15:55:09 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <unistd.h>
# include <fcntl.h>
# include "purplegreensh.h"

typedef struct s_dispatch	t_dispatch;

typedef struct		s_token
{
	char			*src;
	int				type;
# define TOK_COMMON 1
# define TOK_SEP 2
# define TOK_QUOTES 4
# define TOK_RED 8
# define TOK_OR 16
# define TOK_AND 32
# define TOK_COMMA 64
# define TOK_PRE 128
# define TOK_SKULL 256
# define TOK_Q 1024
# define TOK_QF 2048
# define TOK_INI 4096
# define TOK_GLOB 8192
# define TOK_NEEDP 512
# define TOK_HISTO 16384
# define TOK_EQUAL 32768
# define TOK_DOLLAR 65536
# define TOK_REQ (TOK_NEEDP | TOK_GLOB | TOK_HISTO | TOK_EQUAL)

	int				typeoff;
}					t_token;

int					toktype_sep(const char *src, int len);
int					toktype_quote(const char raw);
int					toktype_common(const char *src);

typedef struct		s_red
{
	char			*file;
	int				flag;
# define R_CLOSED 1
# define R_ISRAT 2
# define R_HERE 4

	int				mode;
	int				x;
	int				y;
	int				in;
	int				out;
	struct s_red	*next;
}					t_red;

void				*new_red(void);

typedef struct		s_fdptr
{
	int				fd;
	int				todo;
	char			*ptr;
}					t_fdptr;

typedef struct		s_sl
{
	const char		*s;
	size_t			l;
}					t_sl;

# define CAT_QUOTES 1
# define CAT_QUOTES_FREE 2
# define CAT_SEP 4
# define CAT_RED 8
# define CAT_PRET 16
# define CAT_SUBSHELL 32
# define CAT_STOP 64
# define CAT_SKULLBRACKETS 128
# define CAT_CROCHET 256
# define CAT_SPECTASK 512

int					isoftype(const char *const src);

# define TYPE_ERROR 0
# define TYPE_AND 1
# define TYPE_ANDAND 2
# define TYPE_OR 3
# define TYPE_OROR 4
# define TYPE_COMMA 5
# define TYPE_R 6
# define TYPE_RR 7
# define TYPE_L 8
# define TYPE_LL 9
# define TYPE_LLL 10
# define TYPE_AR 11
# define TYPE_LA 12
# define TYPE_IO 13
# define TYPE_RA 14
# define TYPE_AL 15

# define NO_PATH_PROVIDED "no path provided.\n"
# define ILLEGAL_START "illegal start : %s.\n"
# define ILLEGAL_SUBSHELL "illegal subshell placement.\n"
# define RED_LA_BAD_MOVE "moving file descriptor : bad syntax.\n"
# define RED_DRIGHT "can't open %s for reading.\n"
# define RED_REQ_PATH "redirection required a valid path.\n"
# define ODD_INIBIT "odd error during `CMDS` process %p\n"
# define RED_OPENF "No such file or directory %s.\n"
# define REQ_MALLOC "Memory allocation failure.\n"
# define BAD_OPERATOR "Bad operator %s.\n"
# define UNK_COMMAND "command not found : %s\n"
# define BAD_COMMA "Bad comma separator.\n"
# define FATAL_EXECVE "Fatal error : execve failure.\n%s -- %p\n"
# define FATAL_FORK "Fatal error : fork failure.\n%s\n"
# define FATAL_PIPE "Fatal error : pipe failure.\n%s\n"
# define REQ_QUOTES "quotes \'%c\'> "
# define REQ_QUOTES_SIZE 12
# define BAD_BG_PERCENT "the index given by %s doesn't correspond to any job\n"

typedef struct		s_parse
{
	int				type;
	int				intype;
}					t_parse;

typedef struct		s_back
{
	pid_t			pid;
	int				status;
# define B_RUN 1
# define B_STOPPED 2
# define B_FOREGROUND 4
# define B_BACKGROUND 8

	char			**argv;
	struct s_back	*next;
}					t_back;

typedef struct		s_cmd
{
	pid_t			pid;
	int				stdin;
	int				stdout;
	int				stderr;
	int				type;
# define CMD_OK 0
# define CMD_RED 1
# define CMD_BUILT 2

	int				typeoff;
	int				isdone;
	int				pad;
	void			*func;
	char			**argv;
	struct s_cmd	*next;
	struct s_red	*red;
}					t_cmd;
void				*new_cmd(void);

typedef struct		s_task
{
	int				type;
# define TASK_COMMON 0
# define TASK_SUBSHELL 1
# define TASKI_AND 2
# define TASKI_ANDAND 4
# define TASKI_OR 8
# define TASKI_OROR 16
# define TASKI_COMMA 32

	int				stdin;
	int				stdout;
	int				stderr;
	pid_t			group;
	pid_t			process;
	t_cmd			*cmd;
	t_token			*tokens;
	struct s_task	*next;
	struct s_red	*red;
}					t_task;
void				*new_task(void);

int					ismatching(register const char *glob,
		register const char *name);

typedef struct		s_array
{
	char			**array;
	size_t			size;
	size_t			count;
}					t_array;
void				glob_append(const char *const src, t_array *const a);

typedef struct		s_redinfo
{
	int				mode;
	int				setting;
# define R_PATH 1

	int				in;
	int				out;
	void			(*func)(t_dispatch *const dispatch, t_red *const red);
}					t_redinfo;

void				red_and(t_dispatch *const dispatch, t_red *const red);
void				red_heredoc(t_dispatch *const dispatch, t_red *const red);
void				red_herestring(t_dispatch *const dispatch,
		t_red *const red);

#endif
