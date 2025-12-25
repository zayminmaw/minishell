/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:40:05 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 18:46:23 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "prompt.h"
#include <errno.h>
#include <sys/stat.h>

static int	pipeline_abort(t_node *nodes, int start, int forked_children,
		int ret)
{
	close_all_pipes(&nodes[start]);
	if (forked_children > 0)
		wait_for_n_children(forked_children);
	free_pipes(&nodes[start]);
	return (ret);
}

void	execute_pipeline_child(t_node *node, int cmd_index)
{
	struct stat	path_stat;

	setup_pipe_fds(node, cmd_index);
	handle_redirections(node);
	close_all_pipes(node);
	set_child_signals();
	if (node->type == BUILDIN_CHILD)
	{
		exec_buildin_child(node);
		exit(get_exit_status());
	}
	else if (node->type == BUILDIN_PARENT)
	{
		exec_buildin_parent(node);
		exit(get_exit_status());
	}
	else
	{
		execve(node->exec_path, node->full_cmd, node->env->envp);
		if (ft_strchr(node->full_cmd[0], '/'))
		{
			if (stat(node->full_cmd[0], &path_stat) == 0)
			{
				if (S_ISDIR(path_stat.st_mode))
				{
					ft_file_error(ISDIR_ERR, node->full_cmd[0], 126);
					exit(126);
				}
				ft_file_error(PERM_ERR, node->full_cmd[0], 126);
				exit(126);
			}
			ft_file_error(DIR_ERR, node->full_cmd[0], 127);
		}
		else
			ft_file_error(CMD_ERR, node->full_cmd[0], 127);
		exit(127);
	}
}

static int	handle_pipeline_cmd(t_node *nodes, int *i, int *cmd_index,
		int start, pid_t *last_pid)
{
	(void)start;
	if (nodes[*i].type == PIPE)
	{
		(*i)++;
		return (0);
	}
	return (handle_child_cmd(nodes, i, cmd_index, nodes[start].cmd_count,
			last_pid));
}

/*
** if start node has no fd in env and cmd count it more then one
- it means pipe allocation failed
** we'll skip pipe tokens here
*/
int	execute_pipeline(t_node *nodes, int start)
{
	int		i;
	int		cmd_index;
	int		ret;
	pid_t	last_pid;

	alloc_pipes(&nodes[start]);
	if (!nodes[start].env->fd && nodes[start].cmd_count > 1)
		return (0);
	i = start;
	cmd_index = 0;
	last_pid = -1;
	while (cmd_index < nodes[start].cmd_count)
	{
		ret = handle_pipeline_cmd(nodes, &i, &cmd_index, start, &last_pid);
		if (ret != 0)
		{
			if (ret == 4)
				return (pipeline_abort(nodes, start, cmd_index, 4));
			return (pipeline_abort(nodes, start, cmd_index, 0));
		}
	}
	wait_for_children_with_last(nodes[start].cmd_count, last_pid);
	free_pipes(&nodes[start]);
	return (0);
}
