/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:44:43 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 15:44:45 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	should_skip_execution(t_node_type pending_op, int status)
{
	if (pending_op == DOUBLE_AND && status != 0)
		return (1);
	if (pending_op == DOUBLE_OR && status == 0)
		return (1);
	return (0);
}

void	skip_command_group(t_node *nodes, int *i, t_node_type *pending_op)
{
	if (nodes[*i].cmd_count > 1)
		*i += nodes[*i].real_cmd_count;
	else
		(*i)++;
	*pending_op = ALIEN;
}
