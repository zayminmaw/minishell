/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:40:05 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 19:51:36 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "prompt.h"
#include <errno.h>
#include <sys/stat.h>

// clean up pipeline and wait for children on error
// closes and frees all pipes, waits for forked children
static int	pipeline_abort(t_node *nodes, int start, int forked, int ret)
{
	close_all_pipes(&nodes[start]);
	if (forked > 0)
		wait_for_n_children(forked);
	free_pipes(&nodes[start]);
	return (ret);
}

// execute pipeline child process
// sets up pipes, redirections, and executes command
void	execute_pipeline_child(t_node *node, int cmd_index)
{
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
		if (node->exec_path)
			execve(node->exec_path, node->full_cmd, node->env->envp);
		handle_execve_failure(node);
	}
}

// handle single command in pipeline
// skips pipe tokens and routes commands to handler
static int	handle_pipeline_cmd(t_node *nodes, int *i, int *cmd_index,
		pid_t *last_pid)
{
	int	start;

	start = *i;
	while (nodes[start].cmd_count > 1 && start > 0)
		start--;
	if (nodes[*i].type == PIPE)
	{
		(*i)++;
		return (0);
	}
	return (handle_child_cmd(nodes, i, cmd_index, last_pid));
}

// execute pipeline of commands
// allocates pipes, forks children, and waits for completion
// if start node has no fd in env and cmd count > 1,
// it means pipe allocation failed - skip pipe tokens
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
		ret = handle_pipeline_cmd(nodes, &i, &cmd_index, &last_pid);
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
