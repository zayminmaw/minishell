/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:44:37 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 15:44:39 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "prompt.h"

int	handle_logical_op(t_node *nodes, int *i, t_node_type *pending_op)
{
	if (nodes[*i].type == DOUBLE_AND || nodes[*i].type == DOUBLE_OR)
	{
		*pending_op = nodes[*i].type;
		(*i)++;
		return (1);
	}
	return (0);
}

/* should_skip_execution and skip_command_group moved to executor_helpers2.c */

int	execute_and_advance(t_node *nodes, int *i, t_node_type *pending_op)
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

int	handle_parentheses(t_node *nodes, int *i, t_node_type *pending_op)
{
	int	should_skip;
	int	next_i;
	int	end;

	if (nodes[*i].type != L_PAR)
		return (0);
	if (nodes[*i].cmd_count > 1)
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

int	process_node(t_node *nodes, int *i, t_node_type *pending_op)
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
	if (nodes[*i].type == L_PAR && nodes[*i].cmd_count > 1)
	{
	}
	else if (!is_executable_type(nodes[*i].type))
		return ((*i)++, 0);
	status = get_exit_status();
	if (should_skip_execution(*pending_op, status))
		return (skip_command_group(nodes, i, pending_op), 0);
	return (execute_and_advance(nodes, i, pending_op));
}
