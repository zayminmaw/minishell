/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_wildcard_expand.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 21:30:00 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/18 21:31:15 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

// process one match from expand_in_directory
// recursively expand remaining components
// add all results to result array
char	**process_match_recursive(char *match, char **comp, int idx,
	char **result)
{
	char	**temp;
	int		j;
	int		total;

	total = 0;
	if (result)
	{
		while (result[total])
			total++;
	}
	temp = expand_path_recursive(match, comp, idx + 1);
	if (temp)
	{
		j = 0;
		while (temp[j])
		{
			result = add_match(result, temp[j], &total);
			j++;
		}
		free(temp);
	}
	return (result);
}

// process wildcard component by expanding in directory
// then recursively process each match
static char	**process_wildcard_component(char *prefix, char **comp, int idx)
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

// recursively expand wildcard pattern with path components
// 1. if no more components return prefix or "."
// 2. if component has no wildcard, join prefix and component then recurse
// 3. if component has wildcard, expand in directory and recurse for each
char	**expand_path_recursive(char *prefix, char **components, int idx)
{
	if (!components[idx])
		return (handle_no_components(prefix));
	if (!has_wildcard(components[idx]))
		return (handle_no_wildcard_component(prefix, components, idx));
	return (process_wildcard_component(prefix, components, idx));
}

// get prefix for path expansion
// if token starts with /, return "/", otherwise return ""
static char	*get_path_prefix(char *token)
{
	if (*token == '/')
		return (ft_strdup("/"));
	return (ft_strdup(""));
}

// expand single wildcard token
// if no / in token, expand in current directory
// otherwise split by / and recursively expand each component
// handle leading / and trailing /
char	**expand_wildcard_token(char *token)
{
	char	**components;
	char	**matches;
	char	*prefix;
	int		trailing_slash;

	if (!ft_strchr(token, '/'))
		return (expand_in_directory(".", token));
	trailing_slash = (token[ft_strlen(token) - 1] == '/');
	components = split_path_components(token);
	if (!components)
		return (NULL);
	prefix = get_path_prefix(token);
	matches = expand_path_recursive(prefix, components, 0);
	free(prefix);
	free_components(components);
	if (trailing_slash && matches)
		matches = append_trailing_slash(matches);
	return (matches);
}
