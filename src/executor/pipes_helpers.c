/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:45:50 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 15:45:57 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
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
