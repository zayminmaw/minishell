/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_wildcard_expand.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 21:30:00 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/18 22:03:48 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

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
