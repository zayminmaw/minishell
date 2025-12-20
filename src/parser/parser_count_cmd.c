/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_count_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:51:10 by zmin              #+#    #+#             */
/*   Updated: 2025/12/21 03:00:32 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "parser.h"

// count commands in pipeline, handling parentheses
// skip pipes and right parentheses in count
// return updated index and count
static int	count_pipeline_cmds(t_node *nodes, int i, int *count)
{
	while (i < nodes->env->node_len && (nodes[i].type == BUILDIN_CHILD
			|| nodes[i].type == PIPE || nodes[i].type == CMD
			|| nodes[i].type == BUILDIN_PARENT || nodes[i].type == L_PAR
			|| nodes[i].type == R_PAR))
	{
		if (nodes[i].type == L_PAR)
		{
			i = find_matching_rpar(nodes, i) + 1;
			(*count)++;
		}
		else if (nodes[i].type != PIPE && nodes[i].type != R_PAR)
		{
			(*count)++;
			i++;
		}
		else
			i++;
	}
	return (i);
}

// set command count for all nodes in range
// cmd_count: actual command count
// real_cmd_count: node count including pipes and parentheses
static void	set_cmd_counts(t_node *nodes, int start, int end, int count)
{
	int	real_count;

	real_count = end - start;
	while (start < end)
	{
		nodes[start].cmd_count = count;
		nodes[start].real_cmd_count = real_count;
		start++;
	}
}

// cmd_count: actual command count
// real_cmd_count: node count including pipes
void	parser_count_cmd(t_node *nodes)
{
	int	i;
	int	start;
	int	count;

	i = 0;
	while (i < nodes->env->node_len)
	{
		count = 0;
		if (nodes[i].type == CMD || nodes[i].type == BUILDIN_CHILD
			|| nodes[i].type == BUILDIN_PARENT || nodes[i].type == L_PAR)
		{
			start = i;
			i = count_pipeline_cmds(nodes, i, &count);
			set_cmd_counts(nodes, start, i, count);
		}
		else
			i++;
	}
}
