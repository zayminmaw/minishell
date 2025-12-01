/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_build_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:32:40 by zmin              #+#    #+#             */
/*   Updated: 2025/12/01 18:32:05 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

// skip and set redir
// identify command type
// get command
// count arguments
// fill args into full_cmd array
// skip and set redir
// return pointer of next token
char	**parser_build_nodes(t_node *node, char **tokens, char **envp)
{
	int	args_count;

	tokens = parser_set_inout(node, tokens);
	if (!parser_resolve_nodes(*tokens, node))
		node->exec_path = parser_build_path(envp, *tokens);
	else if (node->type == BUILDIN_CHILD
		|| node->type == BUILDIN_PARENT)
		node->exec_path = ft_strdup(*tokens);
	else
		return (++tokens);
	args_count = parser_count_args(tokens);
	tokens = parser_set_fullcmd(node, args_count, tokens);
	if (*tokens)
		tokens = parser_set_inout(node, tokens);
	return (tokens);
}
