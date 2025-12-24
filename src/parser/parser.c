/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:19:39 by zmin              #+#    #+#             */
/*   Updated: 2025/12/24 21:11:39 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

void	print_node_array(t_node *nodes, int array_size);

// transforming tokens into nodes
// 1. count nodes
// 2. init nodes
// 3. identify/build nodes
// 4. count nodes
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
	return (nodes);
}
// print_node_array(nodes, env->node_len);
// void	print_node_array(t_node *nodes, int array_size)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	printf("\n--- Start of Node Array (Size: %d) ---\n", array_size);
// 	while (i < array_size)
// 	{
// 		printf("\nNode %d Details:\n", i);
// 		printf("  Node Type:       %d\n", nodes[i].type);
// 		printf("  Exec Path:       %s\n",
// 			nodes[i].exec_path ? nodes[i].exec_path : "(NULL)");
// 		printf("  Full Command:    [ ");
// 		if (nodes[i].full_cmd)
// 		{
// 			j = 0;
// 			while (nodes[i].full_cmd[j] != NULL)
// 			{
// 				printf("\"%s\"%s", nodes[i].full_cmd[j], nodes[i].full_cmd[j
// 					+ 1] ? ", " : "");
// 				j++;
// 			}
// 		}
// 		printf(" ]\n");
// 		printf("  In Flag:         %d\n", nodes[i].in_flag);
// 		printf("  Out Flag:        %d\n", nodes[i].out_flag);
// 		printf("  Infiles:         [ ");
// 		if (nodes[i].infiles)
// 		{
// 			j = 0;
// 			while (nodes[i].infiles[j] != NULL)
// 			{
// 				printf("\"%s\"%s", nodes[i].infiles[j], nodes[i].infiles[j
// 					+ 1] ? ", " : "");
// 				j++;
// 			}
// 		}
// 		else
// 			printf("(NULL)");
// 		printf(" ]\n");
// 		printf("  Outfiles:        [ ");
// 		if (nodes[i].outfiles)
// 		{
// 			j = 0;
// 			while (nodes[i].outfiles[j] != NULL)
// 			{
// 				printf("\"%s\"%s", nodes[i].outfiles[j], nodes[i].outfiles[j
// 					+ 1] ? ", " : "");
// 				j++;
// 			}
// 		}
// 		else
// 			printf("(NULL)");
// 		printf(" ]\n");
// 		printf("  Delimiters:      [ ");
// 		if (nodes[i].delimiters)
// 		{
// 			j = 0;
// 			while (nodes[i].delimiters[j] != NULL)
// 			{
// 				printf("\"%s\"%s", nodes[i].delimiters[j], nodes[i].delimiters[j
// 					+ 1] ? ", " : "");
// 				j++;
// 			}
// 		}
// 		else
// 			printf("(NULL)");
// 		printf(" ]\n");
// 		printf("  Cmd Count:       %d\n", nodes[i].cmd_count);
// 		printf("  Real Cmd Count:  %d\n", nodes[i].real_cmd_count);
// 		i++;
// 	}
// 	printf("\n--- End of Node Array ---\n");
// }