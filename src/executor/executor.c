/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:42:20 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 19:06:28 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "prompt.h"
#include <sys/stat.h>

// execute child process for single command
// handles redirections, signals, and command execution
static void	execute_child_process(t_node *node)
{
	handle_redirections(node);
	set_child_signals();
	if (node->type == BUILDIN_CHILD)
	{
		exec_buildin_child(node);
		exit(get_exit_status());
	}
	else
	{
		execve(node->exec_path, node->full_cmd, node->env->envp);
		handle_execve_failure(node);
	}
}

// execute single command (non-pipeline)
// handles builtins, validation, heredoc, and fork
static int	execute_single_cmd(t_node *nodes, int start)
{
	pid_t	pid;
	int		return_status;
	t_node	*node;

	node = &nodes[start];
	if (node->type == BUILDIN_PARENT)
	{
		return_status = exec_buildin_parent(node);
		if (return_status == 1)
			return (4);
		return (0);
	}
	if (validate_infile(node) || validate_outfile(node))
		return (0);
	if (write_heredoc(node, start))
		return (0);
	if (!node->full_cmd || !node->full_cmd[0])
		return (0);
	pid = fork();
	if (pid < 0)
		return (ft_process_error(FORK_ERR, 1), 0);
	if (pid == 0)
		execute_child_process(node);
	wait_and_set_status(pid);
	return (0);
}

// execute command group (pipeline or single command)
// routes to appropriate executor based on command count
int	execute_group(t_node *nodes, int start)
{
	if (nodes[start].cmd_count > 1)
	{
		if (execute_pipeline(nodes, start) == 4)
			return (4);
	}
	else
	{
		if (execute_single_cmd(nodes, start) == 4)
			return (4);
	}
	return (0);
}

// main executor loop
// processes all nodes with logical operators and subshells
int	executor(t_node *nodes)
{
	int			i;
	t_node_type	pending_op;
	int			ret;

	if (!nodes)
		return (0);
	set_execution_signals();
	i = 0;
	pending_op = ALIEN;
	ret = 0;
	while (i < nodes->env->node_len && ret != 4)
	{
		ret = process_node(nodes, &i, &pending_op);
		if (ret == -1)
			break ;
	}
	set_prompt_signals();
	if (ret == 4)
		return (4);
	return (0);
}
