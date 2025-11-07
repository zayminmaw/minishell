/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 22:37:02 by zmin              #+#    #+#             */
/*   Updated: 2025/11/07 20:12:59 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

static int	count_words(char *str)
{
	unsigned int	i;
	unsigned int	flag;
	int				count;

	i = 0;
	flag = 0;
	count = 0;
	while (str[i])
	{
		ft_skipquotes(str, &i);
		if (str[i] != ' ')
			flag = 1;
		else if (str[i] == ' ' && flag)
		{
			flag = 0;
			count++;
		}
		i++;
	}
	if (flag)
		count++;
	return (count);
}
