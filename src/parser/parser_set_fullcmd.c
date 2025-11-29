/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set_fullcmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:08:48 by zmin              #+#    #+#             */
/*   Updated: 2025/11/29 14:32:35 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

char	**parser_set_fullcmd(t_node *node, int args_count, char **tokens)
{
	int	i;

	i = 0;
	node->full_cmd = malloc(sizeof(char *) * (args_count + 1));
	if (!node->full_cmd)
		return (tokens);
	if (node->exec_path)
		node->full_cmd[i++] = ft_strdup(node->exec_path);
	else
		node->full_cmd[i++] = ft_strdup("null");
	tokens++;
	while (i < args_count)
	{
		tokens = parser_set_inout(node, tokens);
		node->full_cmd[i] = ft_strdup(*tokens);
		i++;
		tokens++;
	}
	node->full_cmd[i] = NULL;
	return (tokens);
}
