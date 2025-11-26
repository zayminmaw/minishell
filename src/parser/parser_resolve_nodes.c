/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resolve_nodes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:12:11 by zmin              #+#    #+#             */
/*   Updated: 2025/11/26 20:57:49 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

// Return 1 -> buildin commands
// Return 2 -> operator
// Return 0 -> normal commands
int	parser_resolve_nodes(char *token, t_node *node)
{
	if (!token)
		return (1);
	if (!ft_strcmp(token, "export") || !ft_strcmp(token, "cd")
		|| !ft_strcmp(token, "unset") || !ft_strcmp(token, "exit"))
		return (node->node_type = BUILDIN_PARENT, 1);
	else if (!ft_strcmp(token, "echo") || !ft_strcmp(token, "pwd")
		|| !ft_strcmp(token, "env"))
		return (node->node_type = BUILDIN_CHILD, 1);
	else if (!ft_strcmp(token, "&&"))
		node->node_type = DOUBLE_AND;
	else if (!ft_strcmp(token, "||"))
		node->node_type = DOUBLE_OR;
	else if (!ft_strcmp(token, "|"))
		node->node_type = PIPE;
	else if (!ft_strcmp(token, "("))
		node->node_type = L_PAR;
	else if (!ft_strcmp(token, ")"))
		node->node_type = R_PAR;
	if (node->node_type != ALIEN)
		return (2);
	node->node_type = CMD;
	return (0);
}
