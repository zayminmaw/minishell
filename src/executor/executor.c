/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:42:20 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/08 00:52:39 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"
#include "executor.h"
#include "exit_status.h"
#include "utils.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static void	wait_for_children(int cmd_count)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	while (i < cmd_count)
	{
		wait(&status);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		i++;
	}
	set_exit_status(last_status);
}

static void	execute_pipeline_child(t_node *node, int cmd_index)
{
	setup_pipe_fds(node, cmd_index);
	handle_redirections(node);
	close_all_pipes(node);
	if (node->type == BUILDIN_CHILD)
	{
		exec_buildin_child(node);
		exit(get_exit_status());
	}
	else
	{
		execve(node->exec_path, node->full_cmd, node->env->envp);
		ft_file_error(CMD_ERR, node->full_cmd[0], 127);
		exit(127);
	}
}

/*
** if start node has no fd in env and cmd count it more then one
- it means pipe allocation failed
** we'll skip pipe tokens here
*/
static int	execute_pipeline(t_node *nodes, int start)
{
	int		i;
	int		cmd_index;
	pid_t	pid;

	printf("DEBUG: cmd_count=%d, real_cmd_count=%d, start=%d\n",
		nodes[start].cmd_count, nodes[start].real_cmd_count, start);
	alloc_pipes(&nodes[start]);
	if (!nodes[start].env->fd && nodes[start].cmd_count > 1)
		return (0);
	i = start;
	cmd_index = 0;
	while (cmd_index < nodes[start].cmd_count)
	{
		if (nodes[i].type == PIPE)
		{
			i++;
			continue ;
		}
		if (nodes[i].type == BUILDIN_PARENT)
		{
			close_all_pipes(&nodes[start]);
			if (exec_buildin_parent(&nodes[i]) == 1)
				return (free_pipes(&nodes[start]), 4);
			cmd_index++;
			i++;
			continue ;
		}
		write_heredoc(&nodes[i]);
		pid = fork();
		if (pid < 0)
			return (ft_process_error(FORK_ERR, 1), 0);
		if (pid == 0)
			execute_pipeline_child(&nodes[i], cmd_index);
		cmd_index++;
		i++;
	}
	close_all_pipes(&nodes[start]);
	wait_for_children(nodes[start].cmd_count);
	free_pipes(&nodes[start]);
	return (0);
}

static int	is_executable_type(t_node_type type)
{
	return (type == CMD || type == BUILDIN_CHILD || type == BUILDIN_PARENT);
}

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
	{
		exec_buildin_child(node);
		exit(get_exit_status());
	}
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
	int		exit_status;

	if (node->type == BUILDIN_PARENT)
	{
		exit_status = exec_buildin_parent(node);
		if (exit_status == 1)
			return (4);
		set_exit_status(exit_status);
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

/*
** skip non executable nodes
** check if the node is part of a pipeline
- if so skip entire pipeline after that
** otherwise execute signle command
*/
int	executor(t_node *nodes)
{
	int	i;

	if (!nodes)
		return (0);
	i = 0;
	while (i < nodes->env->node_len)
	{
		if (!is_executable_type(nodes[i].type))
		{
			i++;
			continue ;
		}
		if (nodes[i].cmd_count > 1)
		{
			if (execute_pipeline(nodes, i) == 4)
				return (4);
			i += nodes[i].real_cmd_count;
		}
		else
		{
			if (execute_single_cmd(&nodes[i]) == 4)
				return (4);
			i++;
		}
	}
	return (0);
}
