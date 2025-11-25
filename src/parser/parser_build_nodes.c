/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_build_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:32:40 by zmin              #+#    #+#             */
/*   Updated: 2025/11/25 21:23:55 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

char	**parser_build_nodes(t_node *node, char **tokens, char **envp)
{
	tokens = parser_set_inout(node, tokens);
	(void)envp;
	return (tokens);
}
