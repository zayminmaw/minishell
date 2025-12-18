/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_wildcard_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 23:00:00 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/18 22:03:48 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

// add remaining recursive results to result array
static char	**add_recursive_results(char **result, char **temp, int *total)
{
	int	j;

	j = 0;
	while (temp[j])
	{
		result = add_match(result, temp[j], total);
		j++;
	}
	free(temp);
	return (result);
}

// process one match from expand_in_directory
// recursively expand remaining components
// add all results to result array
char	**process_match_recursive(char *match, char **comp, int idx,
	char **result)
{
	char	**temp;
	int		total;

	total = 0;
	if (result)
	{
		while (result[total])
			total++;
	}
	if (!comp[idx])
	{
		result = add_match(result, ft_strdup(match), &total);
		return (result);
	}
	temp = expand_path_recursive(match, comp, idx);
	if (temp)
		result = add_recursive_results(result, temp, &total);
	return (result);
}

// process wildcard component by expanding in directory
// then recursively process each match
char	**process_wildcard_component(char *prefix, char **comp, int idx)
{
	char	**matches;
	char	**result;
	int		i;

	if (prefix && *prefix)
		matches = expand_in_directory(prefix, comp[idx]);
	else
		matches = expand_in_directory(".", comp[idx]);
	if (!matches)
		return (NULL);
	result = NULL;
	i = 0;
	while (matches[i])
	{
		result = process_match_recursive(matches[i], comp, idx + 1, result);
		free(matches[i]);
		i++;
	}
	free(matches);
	return (result);
}
