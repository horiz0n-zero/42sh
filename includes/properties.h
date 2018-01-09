/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 13:33:10 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/04 15:06:44 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROPERTIES_H
# define PROPERTIES_H

# include <unistd.h>
# include <stddef.h>
# include <stdint.h>

typedef struct		s_properties
{
	char			*location_color;
	char			*separator_string;
	char			*separator_color;
	char			*prompt_string;
	char			*prompt_color;
	char			*text_color;
	char			*builtins_color;
}					t_properties;

# define PROPERTIES_COUNT 7

typedef struct		s_color_header
{
	uint64_t		magic;
# define MAGIC_COLOR 0xF42ABC23FFF36D12

	uint64_t		size;
}					t_color_header;

typedef struct		s_color_section
{
	uint64_t		offset;
	uint64_t		len;
}					t_color_section;

typedef struct		s_select
{
	char			*name;
	const char		*bg;
	const char		*fg;
	size_t			len;
	int				selected;
	int				cursor;
}					t_select;

typedef struct		s_selection
{
	t_select		*array;
	size_t			count;
	size_t			len;
	size_t			coz;
	int				activated;
	int				app;
	const char		*ref;
	size_t			ref_len;
}					t_selection;

# define CAP_COUNT 25
# define CR 0
# define LE 1
# define ND 2
# define UP 3
# define DO 4
# define BL 5
# define RC 6
# define SC 7
# define CL 8
# define CD 9
# define CE 10
# define DC 11
# define VI 12
# define VE 13
# define TI 14
# define TE 15
# define AL 16
# define CM 17
# define VB 18
# define HO 19
# define CH 20
# define US 21
# define UE 22
# define SO 23
# define SE 24

# define TCGETS		0x5401
# define TCSETS		0x5402
# define TCSETSW	0x5403
# define TCSETSF	0x5404
# define TCGETA		0x5405
# define TCSETA		0x5406
# define TCSETAW	0x5407
# define TCSETAF	0x5408
# define TCSBRK		0x5409
# define TCXONC		0x540A
# define TCFLSH		0x540B

#endif
