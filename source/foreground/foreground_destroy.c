/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground_destroy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 10:36:51 by afeuerst          #+#    #+#             */
/*   Updated: 2018/01/03 15:16:19 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "purplegreensh.h"

static inline void	destory_red(t_cmd *const cmd, t_task *const task)
{
	t_red			*ptr;
	t_red			*tmp;

	if (cmd)
		ptr = cmd->red;
	else
		ptr = task->red;
	while (ptr)
	{
		free(ptr->file);
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
}

static inline void	destroy_task(t_task *const task)
{
	int				i;

	i = 0;
	if (task->stdin != STDIN_FILENO)
		close(task->stdin);
	if (task->stdout != STDOUT_FILENO)
		close(task->stdout);
	if (task->stderr != STDERR_FILENO)
		close(task->stderr);
	if (task->tokens)
	{
		while (task->tokens[i].src)
			free(task->tokens[i++].src);
		free(task->tokens);
	}
	destory_red(NULL, task);
}

static inline void	destroy_cmd(t_cmd *const cmd)
{
	if (cmd->stdin != STDIN_FILENO)
		close(cmd->stdin);
	if (cmd->stdout != STDOUT_FILENO)
		close(cmd->stdout);
	if (cmd->stderr != STDERR_FILENO)
		close(cmd->stderr);
	if (cmd->argv && cmd->isdone)
		free(cmd->argv);
	destory_red(cmd, NULL);
}

static inline void	foreground_free(t_dispatch *const dispatch)
{
	int				i;

	i = 0;
	dispatch->foreground.index = 0;
	dispatch->foreground.need_task = false;
	dispatch->foreground.collection.task = NULL;
	dispatch->foreground.collection.ctask = NULL;
	dispatch->foreground.collection.ccmd = NULL;
	if (dispatch->foreground.tokens)
	{
		while (dispatch->foreground.tokens[i].src)
			free(dispatch->foreground.tokens[i++].src);
		free(dispatch->foreground.tokens);
	}
	dispatch->foreground.tokens = NULL;
}

void				foreground_destroy(t_dispatch *const dispatch)
{
	t_task			*task;
	t_cmd			*cmd;
	void			*tmp;

	task = dispatch->foreground.collection.task;
	while (task)
	{
		cmd = task->cmd;
		while (cmd)
		{
			tmp = cmd;
			destroy_cmd(cmd);
			cmd = cmd->next;
			free(tmp);
		}
		tmp = task;
		destroy_task(task);
		task = task->next;
		free(tmp);
	}
	foreground_free(dispatch);
}
