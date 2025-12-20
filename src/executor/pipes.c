/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:46:02 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/21 03:00:32 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

static void	clean_pipes_on_error(int i, t_node *nodes)
{
	while (--i >= 0)
		free(nodes->env->fd[i]);
	free(nodes->env->fd);
	nodes->env->fd = NULL;
}

void	alloc_pipes(t_node *nodes)
{
	int	i;
	int	pipe_count;

	if (!nodes || nodes->cmd_count <= 1)
		return ;
	pipe_count = nodes->cmd_count - 1;
	nodes->env->fd = malloc(sizeof(int *) * pipe_count);
	if (!nodes->env->fd)
	{
		ft_process_error(MEM_ERR, 1);
		return ;
	}
	i = -1;
	while (++i < pipe_count)
	{
		nodes->env->fd[i] = malloc(sizeof(int) * 2);
		if (!nodes->env->fd[i])
		{
			clean_pipes_on_error(i, nodes);
			ft_process_error(MEM_ERR, 1);
			return ;
		}
		if (pipe(nodes->env->fd[i]) < 0)
		{
			free(nodes->env->fd[i]);
			clean_pipes_on_error(i, nodes);
			ft_process_error(PIPE_ERR, 1);
			return ;
		}
	}
}

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

/*
** First command: only redirect stdout to pipe
** Last command : only redirect stdin from pipe
** Middle commands : redirect both stdin and out
*/
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
