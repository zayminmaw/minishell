/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:45:22 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 18:45:56 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int	wait_for_n_children(int n)
{
	int		status;
	int		i;
	pid_t	ret;

	i = 0;
	while (i < n)
	{
		ret = waitpid(-1, &status, 0);
		if (ret == -1)
		{
			if (errno == EINTR)
				continue ;
			break ;
		}
		i++;
	}
	return (0);
}

void	close_pipe_fd(int fd)
{
	if (fd >= 0)
		close(fd);
}

void	close_pipes_after_fork(t_node *node, int cmd_index)
{
	int	**fd;

	fd = node->env->fd;
	if (!fd)
		return ;
	if (cmd_index == 0)
		close_pipe_fd(fd[0][1]);
	else if (cmd_index == node->cmd_count - 1)
		close_pipe_fd(fd[cmd_index - 1][0]);
	else if (cmd_index > 0 && cmd_index < node->cmd_count - 1)
	{
		close_pipe_fd(fd[cmd_index - 1][0]);
		close_pipe_fd(fd[cmd_index][1]);
	}
}

int	pipeline_abort(t_node *nodes, int start, int forked_children, int ret)
{
	close_all_pipes(&nodes[start]);
	if (forked_children > 0)
		wait_for_n_children(forked_children);
	free_pipes(&nodes[start]);
	return (ret);
}

int	process_subshell_heredocs(t_node *nodes, int start, int end)
{
	int	i;
	int	matching_rpar;

	i = start + 1;
	while (i < end)
	{
		if (nodes[i].type == L_PAR)
		{
			matching_rpar = find_matching_rpar(nodes, i);
			if (matching_rpar < 0)
				return (-1);
			if (process_subshell_heredocs(nodes, i, matching_rpar) < 0)
				return (-1);
			i = matching_rpar + 1;
			continue ;
		}
		if (write_heredoc(&nodes[i], i))
			return (-1);
		if (nodes[i].in_flag == 2)
			nodes[i].in_flag = 1;
		i++;
	}
	return (0);
}
