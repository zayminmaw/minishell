/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_build_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:32:40 by zmin              #+#    #+#             */
/*   Updated: 2025/11/27 20:32:52 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

char	**parser_build_nodes(t_node *node, char **tokens, char **envp)
{
	tokens = parser_set_inout(node, tokens);
	if (!parser_resolve_nodes(*tokens, node))
		node->exec_path = parser_build_path(envp, *tokens);
	else if (node->node_type == BUILDIN_CHILD
		|| node->node_type == BUILDIN_PARENT)
		node->exec_path = ft_strdup(*tokens);
	else
		return (++tokens);
	return (tokens);
}
