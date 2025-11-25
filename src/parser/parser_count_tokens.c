/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_count_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:46:02 by zmin              #+#    #+#             */
/*   Updated: 2025/11/25 19:51:09 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

int	parser_count_tokens(char **tokens)
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
