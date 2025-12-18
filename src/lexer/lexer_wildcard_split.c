/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_wildcard_split.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 21:45:00 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/18 21:58:42 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

// count number of path components (separated by /)
static int	count_components(char *token)
{
	int	count;
	int	i;

	count = 1;
	i = -1;
	while (token[++i])
		if (token[i] == '/')
			count++;
	return (count);
}

// fill result array with path components
static void	fill_components(char **result, char *token, int *count)
{
	int	i;
	int	start;

	i = 0;
	*count = 0;
	start = 0;
	while (token[i])
	{
		if (token[i] == '/')
		{
			if (i > start)
				result[(*count)++] = ft_substr(token, start, i - start);
			start = i + 1;
		}
		i++;
	}
	if (i > start)
		result[(*count)++] = ft_substr(token, start, i - start);
	result[*count] = NULL;
}

// split path into components separated by /
// count slashes to determine array size
// allocate and fill array with path components
// return NULL-terminated array
char	**split_path_components(char *token)
{
	char	**result;
	int		count;
	int		comp_count;
	int		i;

	count = count_components(token);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i <= count)
	{
		result[i] = NULL;
		i++;
	}
	fill_components(result, token, &comp_count);
	return (result);
}

// append trailing slash to directories in matches array
// check each match if it's a directory
// if yes, append / to the path
// return modified matches array
char	**append_trailing_slash(char **matches)
{
	int		i;
	char	*temp;

	if (!matches)
		return (NULL);
	i = 0;
	while (matches[i])
	{
		if (is_directory(matches[i]))
		{
			temp = ft_strjoin(matches[i], "/");
			if (temp)
			{
				free(matches[i]);
				matches[i] = temp;
			}
		}
		i++;
	}
	return (matches);
}
