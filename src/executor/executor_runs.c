/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_runs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:44:49 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 20:07:56 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "prompt.h"

void	execute_child_process(t_node *node)
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
		if (node->exec_path)
			execve(node->exec_path, node->full_cmd, node->env->envp);
		handle_execve_failure(node);
	}
}

static int	perform_fork_and_wait(t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_process_error(FORK_ERR, 1);
		return (0);
	}
	if (pid == 0)
		execute_child_process(node);
	wait_and_set_status(pid);
	return (0);
}

int	execute_single_cmd(t_node *nodes, int start)
{
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
	return (perform_fork_and_wait(node));
}
