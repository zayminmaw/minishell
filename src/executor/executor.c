/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:42:20 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/11 19:16:39 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "prompt.h"

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
	int		return_status;

	if (node->type == BUILDIN_PARENT)
	{
		return_status = exec_buildin_parent(node);
		if (return_status == 1)
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

static int	handle_logical_op(t_node *nodes, int *i, t_node_type *pending_op)
{
	if (nodes[*i].type == DOUBLE_AND || nodes[*i].type == DOUBLE_OR)
	{
		*pending_op = nodes[*i].type;
		(*i)++;
		return (1);
	}
	return (0);
}

static int	should_skip_execution(t_node_type pending_op, int status)
{
	if (pending_op == DOUBLE_AND && status != 0)
		return (1);
	if (pending_op == DOUBLE_OR && status == 0)
		return (1);
	return (0);
}

static void	skip_command_group(t_node *nodes, int *i, t_node_type *pending_op)
{
	if (nodes[*i].cmd_count > 1)
		*i += nodes[*i].real_cmd_count;
	else
		(*i)++;
	*pending_op = ALIEN;
}

static int	execute_and_advance(t_node *nodes, int *i, t_node_type *pending_op)
{
	int	ret;

	ret = execute_group(nodes, *i);
	if (ret == 4)
		return (4);
	if (nodes[*i].cmd_count > 1)
		*i += nodes[*i].real_cmd_count;
	else
		(*i)++;
	*pending_op = ALIEN;
	return (0);
}

static int	handle_parentheses(t_node *nodes, int *i, t_node_type *pending_op)
{
	int	should_skip;
	int	next_i;
	int	end;

	if (nodes[*i].type != L_PAR)
		return (0);
	should_skip = should_skip_execution(*pending_op, get_exit_status());
	if (should_skip)
	{
		end = find_matching_rpar(nodes, *i);
		if (end < 0)
			return (-1);
		*i = end + 1;
	}
	else
	{
		next_i = execute_subshell_group(nodes, *i);
		if (next_i < 0)
			return (-1);
		*i = next_i;
	}
	*pending_op = ALIEN;
	return (1);
}

static int	process_node(t_node *nodes, int *i, t_node_type *pending_op)
{
	int	status;
	int	ret;

	if (handle_logical_op(nodes, i, pending_op))
		return (0);
	ret = handle_parentheses(nodes, i, pending_op);
	if (ret != 0)
		return (ret);
	if (nodes[*i].type == R_PAR)
		return ((*i)++, 0);
	if (!is_executable_type(nodes[*i].type))
		return ((*i)++, 0);
	status = get_exit_status();
	if (should_skip_execution(*pending_op, status))
		return (skip_command_group(nodes, i, pending_op), 0);
	return (execute_and_advance(nodes, i, pending_op));
}

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
