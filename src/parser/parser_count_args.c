/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_count_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 13:17:46 by zmin              #+#    #+#             */
/*   Updated: 2025/11/29 13:31:56 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

// count args of command
// loop until they see |, ||, &&, (, )
// if met with redir >, <, >>, << reduce count for
// file name (if applicable) and redir operator
int	parser_count_args(char **tokens)
{
	int	i;

	i = 0;
	while (*tokens && ft_strncmp(*tokens, "|", 2) && ft_strncmp(*tokens, "||",
			3) && ft_strncmp(*tokens, "&&", 3) && ft_strncmp(*tokens, "(", 2)
		&& ft_strncmp(*tokens, ")", 2))
	{
		if (!ft_strncmp(*tokens, ">", 2) || !ft_strncmp(*tokens, "<", 2)
			|| !ft_strncmp(*tokens, ">>", 3) || !ft_strncmp(*tokens, "<<", 3))
		{
			if (*(tokens + 1))
				i -= 2;
			else
				i--;
		}
		i++;
		tokens++;
	}
	return (i);
}
