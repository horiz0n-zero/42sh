/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 13:42:20 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/17 13:12:21 by jeblonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include <unistd.h>
# include <stdint.h>

typedef struct s_dispatch	t_dispatch;

typedef struct	s_history_node
{
	char		*src;
	uint64_t	len;
	uint32_t	index;
	uint32_t	pad;
}				t_history_node;

typedef struct	s_history_section
{
	uint64_t	offset;
	size_t		len;
	uint32_t	index;
	uint32_t	pad;
}				t_history_section;

typedef struct	s_history_header
{
	uint64_t	magic;
# define MAGIC_HISTO 0xFDAF0BF01F34266F

	uint64_t	sections_count;
	uint64_t	file_size;
}				t_history_header;

int				histo_c(t_dispatch *const dispatch);
int				histo_d(t_dispatch *const dispatch, char **argv);
int				histo_a(t_dispatch *const dispatch);
int				histo_w(t_dispatch *const dispatch);

#endif
