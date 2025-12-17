/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_nodes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:00:04 by zmin              #+#    #+#             */
/*   Updated: 2025/12/17 02:50:36 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

// init empty nodes
t_node	*parser_init_nodes(t_env *env)
{
	t_node	*nodes;
	int		i;

	nodes = malloc(sizeof(t_node) * env->node_len);
	if (!nodes)
		return (ft_process_error(MEM_ERR, 2));
	i = 0;
	while (i < env->node_len)
	{
		nodes[i].full_cmd = NULL;
		nodes[i].exec_path = NULL;
		nodes[i].infile = NULL;
		nodes[i].outfile = NULL;
		nodes[i].delimiters = NULL;
		nodes[i].in_flag = 0;
		nodes[i].out_flag = 0;
		nodes[i].type = ALIEN;
		nodes[i].env = env;
		nodes[i].cmd_count = 0;
		i++;
	}
	return (nodes);
}
