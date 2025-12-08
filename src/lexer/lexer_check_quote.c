/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:26:17 by zmin              #+#    #+#             */
/*   Updated: 2025/12/08 19:26:36 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// If the quote is unmatch will return 1 and if match 0
// unmatched as in not a pair
int	lexer_check_quote(char **tokens)
{
	int		i;
	int		j;
	char	q;

	i = 0;
	while (tokens[i])
	{
		j = 0;
		q = 0;
		while (tokens[i][j])
		{
			if (!q && (tokens[i][j] == '\'' || tokens[i][j] == '"'))
				q = tokens[i][j];
			else if (q && tokens[i][j] == q)
				q = 0;
			j++;
		}
		if (q)
			return (1);
		i++;
	}
	return (0);
}
