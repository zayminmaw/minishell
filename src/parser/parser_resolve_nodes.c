/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resolve_nodes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:12:11 by zmin              #+#    #+#             */
/*   Updated: 2025/11/29 15:59:43 by zmin             ###   ########.fr       */
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
		return (node->type = BUILDIN_PARENT, 1);
	else if (!ft_strcmp(token, "echo") || !ft_strcmp(token, "pwd")
		|| !ft_strcmp(token, "env"))
		return (node->type = BUILDIN_CHILD, 1);
	else if (!ft_strcmp(token, "&&"))
		node->type = DOUBLE_AND;
	else if (!ft_strcmp(token, "||"))
		node->type = DOUBLE_OR;
	else if (!ft_strcmp(token, "|"))
		node->type = PIPE;
	else if (!ft_strcmp(token, "("))
		node->type = L_PAR;
	else if (!ft_strcmp(token, ")"))
		node->type = R_PAR;
	if (node->type != ALIEN)
		return (2);
	node->type = CMD;
	return (0);
}
