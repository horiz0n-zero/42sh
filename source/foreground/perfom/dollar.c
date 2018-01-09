/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 11:27:20 by afeuerst          #+#    #+#             */
/*   Updated: 2017/12/06 15:15:08 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static size_t	dollar_qmark_len(t_dispatch *const dispatch, char **src)
{
	char		*add;
	size_t		len;

	add = string_stc_itoa(dispatch->foreground.status);
	len = ft_strlen(add);
	*src = *src + 2;
	return (len);
}

size_t			dollar_len(t_dispatch *const dispatch, char **src)
{
	char		tmp;
	char		*start;
	char		*res;

	start = *src + 1;
	if (*start == '?')
		return (dollar_qmark_len(dispatch, src));
	while (*start >= 'A' && *start <= 'Z')
		start++;
	tmp = *start;
	*start = 0;
	res = SUPER(dispatch)->env.get(dispatch, *src + 1);
	if (!res)
		res = "";
	*start = tmp;
	*src = start;
	return (ft_strlen(res));
}

/*
***
**** $$ (shell pid) $? (last status) $! (last pid) $0 (42sh)
***
*/

static void		*dollar_qmark_push(t_dispatch *const dispatch, char **src,
		char *dst)
{
	char		*add;

	add = string_stc_itoa(dispatch->foreground.status);
	*src = *src + 2;
	while (*add)
		*dst++ = *add++;
	return (dst);
}

void			*dollar_push(t_dispatch *const dispatch, char **src, char *dst)
{
	char		tmp;
	char		*start;
	char		*res;

	start = *src + 1;
	if (*start == '?')
		return (dollar_qmark_push(dispatch, src, dst));
	while (*start >= 'A' && *start <= 'Z')
		start++;
	tmp = *start;
	*start = 0;
	if (!(res = SUPER(dispatch)->env.get(dispatch, *src + 1)))
		res = "";
	*start = tmp;
	while (*res)
		*dst++ = *res++;
	*src = start;
	return (dst);
}
