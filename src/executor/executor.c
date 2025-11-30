/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:42:20 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/11/30 19:07:01 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"
#include "executor.h"
#include "exit_status.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static void	execute_child_process(t_node *node)
{
	if (node->type == BUILDIN_CHILD)
		exec_buildin_child(node);
	else
	{
		execve(node->exec_path, node->full_cmd, node->env->envp);
		perror(node->full_cmd[0]);
		exit(127);
	}
}

static void	wait_and_set_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		set_exit_status(WEXITSTATUS(status));
}

static void	execute_single_cmd(t_node *node)
{
	pid_t	pid;
	int		status;

	if (node->type == BUILDIN_PARENT)
	{
		status = exec_buildin_parent(node);
		set_exit_status(status);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		set_exit_status(1);
		return ;
	}
	if (pid == 0)
		execute_child_process(node);
	wait_and_set_status(pid);
}

void	executor(t_node *nodes)
{
	int i;

	if (!nodes)
		return ;
	i = 0;
	while (i < nodes->env->node_len)
	{
		execute_single_cmd(&nodes[i]);
		i++;
	}
}