/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:46:02 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 19:06:28 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "executor.h"

// clean up allocated pipes on error
// frees all previously allocated pipe pairs
static void	clean_pipes_on_error(int i, t_node *nodes)
{
	while (--i >= 0)
		free(nodes->env->fd[i]);
	free(nodes->env->fd);
	nodes->env->fd = NULL;
}

// initialize a single pipe pair
// allocates memory and creates pipe file descriptors
static int	init_pipe_pair(t_node *nodes, int i)
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

// allocate pipes for pipeline
// creates cmd_count-1 pipes for command pipeline
void	alloc_pipes(t_node *nodes)
{
	int	i;
	int	ret;

	if (!nodes || nodes->cmd_count <= 1)
		return ;
	nodes->env->fd = malloc(sizeof(int *) * (nodes->cmd_count - 1));
	if (!nodes->env->fd)
	{
		ft_process_error(MEM_ERR, 1);
		return ;
	}
	i = -1;
	while (++i < nodes->cmd_count - 1)
	{
		ret = init_pipe_pair(nodes, i);
		if (ret != 0)
		{
			clean_pipes_on_error(i, nodes);
			ft_process_error(ret, 1);
			return ;
		}
	}
}

// free all allocated pipes
// releases memory for pipe file descriptors
void	free_pipes(t_node *nodes)
{
	int	i;
	int	pipe_count;

	if (!nodes || !nodes->env || !nodes->env->fd)
		return ;
	pipe_count = nodes->cmd_count - 1;
	i = 0;
	while (i < pipe_count)
	{
		free(nodes->env->fd[i]);
		i++;
	}
	free(nodes->env->fd);
	nodes->env->fd = NULL;
}

// setup pipe file descriptors for command
// redirects stdin/stdout to appropriate pipe ends
void	setup_pipe_fds(t_node *node, int cmd_index)
{
	int	**fd;

	if (!node || !node->env || !node->env->fd)
		return ;
	fd = node->env->fd;
	if (cmd_index == 0 && node->out_flag == 0)
	{
		if (dup2(fd[0][1], STDOUT_FILENO) < 0)
			ft_process_error(DUP_ERR, 1);
	}
	else if (cmd_index == node->cmd_count - 1 && node->in_flag == 0)
	{
		if (dup2(fd[cmd_index - 1][0], STDIN_FILENO) < 0)
			ft_process_error(DUP_ERR, 1);
	}
	else if (cmd_index > 0 && cmd_index < (node->cmd_count - 1))
		redirect_middile_command(fd, node, cmd_index);
}
