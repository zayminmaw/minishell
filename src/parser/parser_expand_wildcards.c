/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_wildcards.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/18 21:31:15 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

// copy matches to result at index position
// return the number of elements copied
static int	insert_matches(char **result, char **matches, int pos)
{
	int	k;

	k = 0;
	while (matches && matches[k])
	{
		result[pos + k] = matches[k];
		k++;
	}
	return (k);
}

// copy matches to result array at current position
// free the original token and matches array
static int	copy_matches_to_result(char **result, char **tokens, char **matches,
	int idx)
{
	int	i;
	int	j;
	int	match_count;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (i == idx)
		{
			match_count = insert_matches(result, matches, j);
			j += match_count;
			free(tokens[i]);
			if (matches)
				free(matches);
		}
		else
			result[j++] = tokens[i];
		i++;
	}
	return (j);
}

// replace single token with array of matched filenames
// allocate new array with size adjusted for matches
// copy all tokens, replacing the wildcard token with matches
// return new array
char	**replace_token_with_matches(char **tokens, int idx, char **matches)
{
	char	**result;
	int		mc;
	int		tc;
	int		total;

	mc = 0;
	while (matches && matches[mc])
		mc++;
	tc = 0;
	while (tokens[tc])
		tc++;
	result = malloc(sizeof(char *) * (tc - 1 + mc + 1));
	if (!result)
		return (tokens);
	total = copy_matches_to_result(result, tokens, matches, idx);
	result[total] = NULL;
	free(tokens);
	return (result);
}

// process wildcard token and update tokens array
// expand token and replace if matches found
// return new index position
static int	process_wildcard(char ***tokens, int i)
{
	char	**matches;
	int		count;

	matches = expand_wildcard_token((*tokens)[i]);
	if (matches && matches[0])
	{
		count = 0;
		while (matches[count])
			count++;
		*tokens = replace_token_with_matches(*tokens, i, matches);
		return (i + count);
	}
	if (matches)
		free(matches);
	return (i + 1);
}

// expand all wildcard tokens in token array
// skip tokens after redirection operators
// for each wildcard token, expand and replace with matches
// return modified token array
char	**expand_wildcards(char **tokens)
{
	int	i;
	int	skip_next;

	if (!tokens)
		return (NULL);
	i = 0;
	skip_next = 0;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "<") || !ft_strcmp(tokens[i], ">")
			|| !ft_strcmp(tokens[i], "<<") || !ft_strcmp(tokens[i], ">>"))
			skip_next = 1;
		else if (skip_next)
			skip_next = 0;
		else if (has_wildcard(tokens[i]))
		{
			i = process_wildcard(&tokens, i);
			continue ;
		}
		i++;
	}
	return (tokens);
}
