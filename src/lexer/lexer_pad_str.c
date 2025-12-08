/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_pad_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 22:11:28 by zmin              #+#    #+#             */
/*   Updated: 2025/12/08 19:12:42 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

// copy everythin inside the quote ' or " into padded_str
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

// padding for shell special characters with spaces
// It checks for two-character operators (>>, <<, &&, ||)
// 1. adds a preceding space if needed
// 2. copies the two-character operator
// 3. adds a trailing space if the next character isn't already one
// If it's a single character operator (>, <, |, &)
// 1. adds a preceding space if needed
// 2. copies the single character
// 3. adds a trailing space if the next character isn't already one
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
// malloc for padded_str
// mutiply strlen by 3 as in still work in worse case scenario
// iterate the input
// 1. skip_quote aka copy everthing inside the quote
// 2. check if the input[i] is a special shell characters
// 3. else copy the input[i] as its.
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
