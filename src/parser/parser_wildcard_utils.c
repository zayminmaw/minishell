/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_wildcard_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 21:30:00 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/18 21:31:15 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <sys/stat.h>

// check if token contains wildcard * outside of quotes
// return 1 if wildcard found, 0 otherwise
int	has_wildcard(char *token)
{
	int		i;
	int		in_quote;
	char	quote_char;

	i = 0;
	in_quote = 0;
	quote_char = 0;
	while (token[i])
	{
		if (!in_quote && (token[i] == '\'' || token[i] == '"'))
		{
			in_quote = 1;
			quote_char = token[i];
		}
		else if (in_quote && token[i] == quote_char)
			in_quote = 0;
		else if (!in_quote && token[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

// join directory path with filename
// handle cases where dir is NULL or "."
// return allocated joined path
char	*join_path(char *dir, char *name)
{
	char	*tmp;
	char	*result;

	if (!dir || !ft_strcmp(dir, "."))
		return (ft_strdup(name));
	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, name);
	free(tmp);
	return (result);
}

// add new match to array of matches
// reallocate array to fit new match
// increment count
// return new array
char	**add_match(char **matches, char *new_match, int *count)
{
	char	**new_arr;
	int		i;

	new_arr = malloc(sizeof(char *) * (*count + 2));
	if (!new_arr)
		return (matches);
	i = 0;
	while (i < *count)
	{
		new_arr[i] = matches[i];
		i++;
	}
	new_arr[*count] = new_match;
	new_arr[*count + 1] = NULL;
	(*count)++;
	if (matches)
		free(matches);
	return (new_arr);
}

// free array of path components
void	free_components(char **components)
{
	int	i;

	if (!components)
		return ;
	i = 0;
	while (components[i])
	{
		free(components[i]);
		i++;
	}
	free(components);
}

// check if path is a directory using stat
// return 1 if directory, 0 otherwise
int	is_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0)
		return (S_ISDIR(st.st_mode));
	return (0);
}
