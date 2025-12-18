/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_wildcard_components.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:00:00 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/18 21:54:34 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

// handle case when no more components left
// return array with prefix or "." as single element
char	**handle_no_components(char *prefix)
{
	char	**result;

	result = malloc(sizeof(char *) * 2);
	if (!result)
		return (NULL);
	if (prefix && *prefix)
		result[0] = ft_strdup(prefix);
	else
		result[0] = ft_strdup(".");
	result[1] = NULL;
	return (result);
}

// handle non-wildcard component by joining and recursing
char	**handle_no_wildcard_component(char *prefix, char **comp, int idx)
{
	char	**result;
	char	*new_prefix;

	if (prefix && *prefix)
		new_prefix = join_path(prefix, comp[idx]);
	else
		new_prefix = join_path(".", comp[idx]);
	result = expand_path_recursive(new_prefix, comp, idx + 1);
	free(new_prefix);
	return (result);
}
