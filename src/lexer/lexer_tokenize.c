/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 22:37:02 by zmin              #+#    #+#             */
/*   Updated: 2025/12/08 19:25:06 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

// count the number of words/tokens respecting quotes
// use flag to identify token
static int	count_words(char *str)
{
	int	i;
	int	flag;
	int	count;

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

// loop until end of the string or unquoted whitespace
static void	escape_quote_and_interate(char *str, char *q, int *i)
{
	while (str[*i] && (!ft_isspace(str[*i]) || *q))
	{
		if (!*q && (str[*i] == '\'' || str[*i] == '"'))
			*q = str[*i];
		else if (*q && str[*i] == *q)
			*q = 0;
		(*i)++;
	}
}

// split the padded str into tokens (str array)
// 1. malloc requite size by counting words
// 2. interate the string skipping spaces
// 3. if i is bigger than start, substr the str and put in tokens
// 4. NULL terminate
char	**lexer_tokenize(char *str)
{
	char	**tokens;
	int		i;
	int		start;
	int		k;
	char	q;

	if (!str)
		return (NULL);
	tokens = malloc(sizeof(char *) * (count_words(str) + 1));
	if (!tokens)
		return (ft_process_error(MEM_ERR, 2));
	i = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		start = i;
		q = 0;
		escape_quote_and_interate(str, &q, &i);
		if (i > start)
			tokens[k++] = ft_substr(str, start, i - start);
	}
	tokens[k] = NULL;
	return (tokens);
}
