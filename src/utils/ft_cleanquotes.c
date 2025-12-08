/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:54:45 by zmin              #+#    #+#             */
/*   Updated: 2025/12/08 20:51:10 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// 1. skip the found quote
// 2. copy the value until the quote is found
// 3. skip the end quote
static void	parse_inside_quote(char *token, char *res, int *i, int *j)
{
	char	q;

	q = token[(*i)++];
	while (token[(*i)] && token[(*i)] != q)
		res[(*j)++] = token[(*i)++];
	if (token[(*i)] == q)
		(*i)++;
}

// remove quotes from token
// 1. malloc for res str
// 2. if a quote is found only take the content of the quote
// 3. else copy as usual
// 4. null terminate and free old token
char	*ft_cleanquotes(char *token)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(sizeof(char) * ft_strlen(token) + 1);
	if (!res)
		return (ft_process_error(MEM_ERR, 2));
	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '"')
		{
			parse_inside_quote(token, res, &i, &j);
		}
		else
			res[j++] = token[i++];
	}
	res[j] = '\0';
	free(token);
	return (res);
}
