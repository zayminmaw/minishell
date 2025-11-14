/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:54:45 by zmin              #+#    #+#             */
/*   Updated: 2025/11/14 19:53:25 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	parse_inside_quote(char *token, char *res, int *i, int *j)
{
	char	q;

	q = token[(*i)++];
	while (token[(*i)] && token[(*i)] != q)
		res[(*j)++] = token[(*i)++];
	if (token[(*i)] == q)
		(*i)++;
}

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
