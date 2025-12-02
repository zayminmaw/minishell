/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:42:20 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/02 23:34:36 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"
#include "executor.h"
#include "exit_status.h"
#include "utils.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static int	validate_infile(t_node *node)
{
	if (node->in_flag != 1)
		return (0);
	if (access(node->infile, F_OK) < 0)
		return (ft_file_error(DIR_ERR, node->infile, 1), 1);
	if (access(node->infile, R_OK) < 0)
		return (ft_file_error(PERM_ERR, node->infile, 1), 1);
	return (0);
}

static int	validate_outfile(t_node *node)
{
	if (node->out_flag == 0)
		return (0);
	if (access(node->outfile, F_OK) == 0 && access(node->outfile, W_OK) < 0)
		return (ft_file_error(PERM_ERR, node->outfile, 1), 1);
	return (0);
}

static void	execute_child_process(t_node *node)
{
	handle_redirections(node);
	if (node->type == BUILDIN_CHILD)
		exec_buildin_child(node);
	else
	{
		execve(node->exec_path, node->full_cmd, node->env->envp);
		ft_file_error(CMD_ERR, node->full_cmd[0], 127);
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

static int	execute_single_cmd(t_node *node)
{
	pid_t	pid;

	if (node->type == BUILDIN_PARENT)
	{
		if (exec_buildin_parent(node))
			return (4);
		return (0);
	}
	if (validate_infile(node) || validate_outfile(node))
		return (0);
	write_heredoc(node);
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

int	executor(t_node *nodes)
{
	int	i;

	if (!nodes)
		return (0);
	i = 0;
	while (i < nodes->env->node_len)
	{
		if (execute_single_cmd(&nodes[i]) == 4)
			return (4);
		i++;
	}
	return (0);
}
