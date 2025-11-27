/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_count_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 20:19:10 by zmin              #+#    #+#             */
/*   Updated: 2025/11/27 20:19:38 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

// Count how many nodes (commands and operators) are in token list
// Each command counts onace, no matter how many arguments it has
// Each operator is also it's own node
int	parser_count_nodes(char **tokens)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (*tokens)
	{
		if (ft_strncmp(*tokens, "|", 2) && ft_strncmp(*tokens, "||", 3)
			&& ft_strncmp(*tokens, "&&", 3) && ft_strncmp(*tokens, "(", 2)
			&& ft_strncmp(*tokens, ")", 2))
		{
			if (!flag)
			{
				flag = 1;
				i++;
			}
		}
		else
		{
			flag = 0;
			i++;
		}
		tokens++;
	}
	return (i);
}
