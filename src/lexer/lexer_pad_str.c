/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_pad_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 22:11:28 by zmin              #+#    #+#             */
/*   Updated: 2025/11/25 19:17:49 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

static void	skip_quote(char *input, char *padded_str, int *i, int *j)
{
	char	q;

	q = input[(*i)++];
	padded_str[(*j)++] = q;
	while (input[*i] && input[*i] != q)
		padded_str[(*j)++] = input[(*i)++];
	if (input[*i] == q)
		padded_str[(*j)++] = input[(*i)++];
}

static void	pad_string(char *input, char *padded_str, int *i, int *j)
{
	if ((input[*i] == '>' && input[*i + 1] == '>') || (input[*i] == '<'
			&& input[*i + 1] == '<') || (input[*i] == '&' && input[*i
				+ 1] == '&') || (input[*i] == '|' && input[*i + 1] == '|'))
	{
		if (*j > 0 && padded_str[*j - 1] != ' ')
			padded_str[(*j)++] = ' ';
		padded_str[(*j)++] = input[*i];
		padded_str[(*j)++] = input[*i + 1];
		*i += 2;
		if (input[*i] && input[*i] != ' ')
			padded_str[(*j)++] = ' ';
		return ;
	}
	if (*j && padded_str[*j - 1] != ' ')
		padded_str[(*j)++] = ' ';
	padded_str[(*j)++] = input[(*i)++];
	if (input[*i] != ' ')
		padded_str[(*j)++] = ' ';
}

// adding space before and after shell special characters
char	*lexer_pad_str(char *input)
{
	char	*padded_str;
	int		i;
	int		j;

	if (!input)
		return (NULL);
	padded_str = malloc(ft_strlen(input) * 3 + 1);
	if (!padded_str)
		return (ft_process_error(MEM_ERR, 2));
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			skip_quote(input, padded_str, &i, &j);
		else if (ft_strchr("<>|&()", input[i]))
			pad_string(input, padded_str, &i, &j);
		else
			padded_str[j++] = input[i++];
	}
	padded_str[j] = '\0';
	return (padded_str);
}
