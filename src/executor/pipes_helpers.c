/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:45:50 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 19:06:28 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "executor.h"
#include <stdlib.h>

void	clean_pipes_on_error(int i, t_node *nodes)
{
	while (--i >= 0)
		free(nodes->env->fd[i]);
	free(nodes->env->fd);
	nodes->env->fd = NULL;
}

int	init_pipe_pair(t_node *nodes, int i)
{
	nodes->env->fd[i] = malloc(sizeof(int) * 2);
	if (!nodes->env->fd[i])
		return (MEM_ERR);
	if (pipe(nodes->env->fd[i]) < 0)
	{
		free(nodes->env->fd[i]);
		return (PIPE_ERR);
	}
	return (0);
}

// redirect middle command in pipeline
// sets up both input and output pipes
void	redirect_middile_command(int **fd, t_node *node, int cmd_index)
{
	if (node->in_flag == 0)
	{
		if (dup2(fd[cmd_index - 1][0], STDIN_FILENO) < 0)
			ft_process_error(DUP_ERR, 1);
	}
	if (node->out_flag == 0)
	{
		if (dup2(fd[cmd_index][1], STDOUT_FILENO) < 0)
			ft_process_error(DUP_ERR, 1);
	}
}

// close all pipe file descriptors
// used after fork to clean up unused pipes
void	close_all_pipes(t_node *node)
{
	int	i;
	int	pipe_count;

	if (!node || !node->env || !node->env->fd)
		return ;
	pipe_count = node->cmd_count - 1;
	i = 0;
	while (i < pipe_count)
	{
		close(node->env->fd[i][0]);
		close(node->env->fd[i][1]);
		i++;
	}
}
