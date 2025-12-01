/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:19:39 by zmin              #+#    #+#             */
/*   Updated: 2025/12/01 17:06:40 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

void	print_node_array(t_node *nodes, int array_size);

t_node	*parser(char **tokens, t_env *env)
{
	t_node	*nodes;
	int		i;

	i = 0;
	env->fd = NULL;
	env->node_len = parser_count_nodes(tokens);
	nodes = parser_init_nodes(env);
	if (!nodes)
		return (ft_freeenv(env), NULL);
	while (i < env->node_len)
	{
		tokens = parser_build_nodes(&nodes[i], tokens, env->envp);
		i++;
	}
	parser_count_cmd(nodes);
	// print_node_array(nodes, env->node_len);
	return (nodes);
}

void	print_node_array(t_node *nodes, int array_size)
{
	int i = 0;

	printf("\n--- Start of Node Array (Size: %d) ---\n", array_size);

	while (i < array_size)
	{
		printf("\nNode %d Details:\n", i);
		printf("  Node Type:       %d\n", nodes[i].type);
		printf("  Exec Path:       %s\n",
			nodes[i].exec_path ? nodes[i].exec_path : "(NULL)");

		printf("  Full Command:    [ ");
		if (nodes[i].full_cmd)
		{
			int j = 0;
			while (nodes[i].full_cmd[j] != NULL)
			{
				printf("\"%s\"%s", nodes[i].full_cmd[j], nodes[i].full_cmd[j
					+ 1] ? ", " : "");
				j++;
			}
		}
		printf(" ]\n");

		printf("  In Flag:         %d\n", nodes[i].in_flag);
		printf("  Out Flag:        %d\n", nodes[i].out_flag);
		printf("  Infile:          %s\n",
			nodes[i].infile ? nodes[i].infile : "(NULL)");
		printf("  Outfile:         %s\n",
			nodes[i].outfile ? nodes[i].outfile : "(NULL)");
		printf("  Delimiter:       %s\n",
			nodes[i].delimiter ? nodes[i].delimiter : "(NULL)");
		printf("  Cmd Count:       %d\n", nodes[i].cmd_count);
		printf("  Real Cmd Count:  %d\n", nodes[i].real_cmd_count);

		i++;
	}

	printf("\n--- End of Node Array ---\n");
}