/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:42:20 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/08 21:04:28 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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
		if (ft_strchr(node->full_cmd[0], '/'))
			ft_file_error(DIR_ERR, node->full_cmd[0], 127);
		else
			ft_file_error(CMD_ERR, node->full_cmd[0], 127);
		exit(127);
	}
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

static int	execute_group(t_node *nodes, int start)
{
	if (nodes[start].cmd_count > 1)
	{
		if (execute_pipeline(nodes, start) == 4)
			return (4);
	}
	else
	{
		if (execute_single_cmd(&nodes[start]) == 4)
			return (4);
	}
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
	int			i;
	t_node_type	pending_op;
	int			status;
	int			ret;
	int			depth;
	int			j;

	if (!nodes)
		return (0);
	i = 0;
	pending_op = ALIEN;
	while (i < nodes->env->node_len)
	{
		// 1 handle logical opretors and remember them
		if (nodes[i].type == DOUBLE_AND || nodes[i].type == DOUBLE_OR)
		{
			pending_op = nodes[i].type;
			i++;
			continue ;
		}
		// 2. parentheses. skip for now
		if (nodes[i].type == L_PAR)
		{
			depth = 1;
			j = i + 1;
			while (j < nodes->env->node_len && depth > 0)
			{
				if (nodes[j].type == L_PAR)
					depth++;
				else if (nodes[j].type == R_PAR)
					depth--;
				j++;
			}
			// TODO: execute nodes between i+1 and j-1 in subshell
			i = j;
			continue ;
		}
		if (nodes[i].type == R_PAR)
		{
			// unmatched or already handled by R_PAR, skip
			i++;
			continue ;
		}
		if (!is_executable_type(nodes[i].type))
		{
			i++;
			continue ;
		}
		// 4. check to execute as a group cmd
		status = get_exit_status();
		if (pending_op == DOUBLE_AND && status != 0)
		{
			if (nodes[i].cmd_count > 1)
				i += nodes[i].real_cmd_count;
			else
				i++;
			pending_op = ALIEN;
			continue ;
		}
		if (pending_op == DOUBLE_OR && status == 0)
		{
			if (nodes[i].cmd_count > 1)
				i += nodes[i].real_cmd_count;
			else
				i++;
			pending_op = ALIEN;
			continue ;
		}
		// 5. execute the group as single or pipeline
		ret = execute_group(nodes, i);
		if (ret == 4)
			return (4);
		if (nodes[i].cmd_count > 1)
			i += nodes[i].real_cmd_count;
		else
			i++;
		pending_op = ALIEN;
	}
	return (0);
}
