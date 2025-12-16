/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_count_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:51:10 by zmin              #+#    #+#             */
/*   Updated: 2025/12/16 20:31:45 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
			|| nodes[i].type == BUILDIN_PARENT)
		{
			start = i;
			while (i < nodes->env->node_len && (nodes[i].type == BUILDIN_CHILD
					|| nodes[i].type == PIPE || nodes[i].type == CMD
					|| nodes[i].type == BUILDIN_PARENT))
				if (nodes[i++].type != PIPE)
					count++;
			while (start < i)
			{
				nodes[start].cmd_count = count;
				nodes[start].real_cmd_count = count * 2 - 1;
				start++;
			}
		}
		else
			i++;
	}
}
