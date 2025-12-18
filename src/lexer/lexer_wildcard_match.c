/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_wildcard_match.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 21:30:00 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/18 21:54:32 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include <dirent.h>

// recursively match pattern with string
// handle * wildcard by trying all possible positions
// return 1 if match found, 0 otherwise
int	match_pattern(char *str, char *pattern)
{
	if (!*pattern)
		return (!*str);
	if (*pattern == '*')
	{
		if (match_pattern(str, pattern + 1))
			return (1);
		if (*str && match_pattern(str + 1, pattern))
			return (1);
		return (0);
	}
	if (*str == *pattern)
		return (match_pattern(str + 1, pattern + 1));
	return (0);
}

// get directory path for opendir
// return dir if exists and not empty, otherwise return "."
static char	*get_dir_path(char *dir)
{
	if (dir && *dir)
		return (dir);
	return (".");
}

// expand wildcard pattern in given directory
// read directory entries and match against pattern
// skip hidden files (starting with .)
// return array of matching filenames
char	**expand_in_directory(char *dir, char *pattern)
{
	DIR				*dirp;
	struct dirent	*entry;
	char			**matches;
	int				count;
	char			*dir_path;

	matches = NULL;
	count = 0;
	dir_path = get_dir_path(dir);
	dirp = opendir(dir_path);
	if (!dirp)
		return (NULL);
	entry = readdir(dirp);
	while (entry)
	{
		if (entry->d_name[0] != '.' && match_pattern(entry->d_name, pattern))
			matches = add_match(matches, join_path(dir, entry->d_name), &count);
		entry = readdir(dirp);
	}
	closedir(dirp);
	return (matches);
}
