/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_wildcards.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/18 18:20:14 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <dirent.h>
#include <sys/stat.h>

static int	match_pattern(char *str, char *pattern)
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

static int	has_wildcard(char *token)
{
	int	i;
	int	in_quote;
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

static char	*join_path(char *dir, char *name)
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

static char	**add_match(char **matches, char *new_match, int *count)
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

static char	**expand_in_directory(char *dir, char *pattern)
{
	DIR				*dirp;
	struct dirent	*entry;
	char			**matches;
	int				count;

	matches = NULL;
	count = 0;
	dirp = opendir(dir && *dir ? dir : ".");
	if (!dirp)
		return (NULL);
	entry = readdir(dirp);
	while (entry)
	{
		if (entry->d_name[0] != '.' && match_pattern(entry->d_name, pattern))
		{
			matches = add_match(matches, join_path(dir, entry->d_name), &count);
		}
		entry = readdir(dirp);
	}
	closedir(dirp);
	return (matches);
}

static char	**expand_path_recursive(char *prefix, char **components, int idx)
{
	char	**matches;
	char	**result;
	char	**temp;
	int		i;
	int		j;
	int		total;

	if (!components[idx])
	{
		result = malloc(sizeof(char *) * 2);
		if (!result)
			return (NULL);
		result[0] = ft_strdup(prefix && *prefix ? prefix : ".");
		result[1] = NULL;
		return (result);
	}
	if (!has_wildcard(components[idx]))
	{
		char *new_prefix = join_path(prefix && *prefix ? prefix : ".", components[idx]);
		result = expand_path_recursive(new_prefix, components, idx + 1);
		free(new_prefix);
		return (result);
	}
	matches = expand_in_directory(prefix && *prefix ? prefix : ".", components[idx]);
	if (!matches)
		return (NULL);
	result = NULL;
	total = 0;
	i = 0;
	while (matches[i])
	{
		temp = expand_path_recursive(matches[i], components, idx + 1);
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
		free(matches[i]);
		i++;
	}
	free(matches);
	return (result);
}

static char	**split_path_components(char *token)
{
	char	**result;
	int		count;
	int		i;
	int		start;

	count = 1;
	i = 0;
	while (token[i])
	{
		if (token[i] == '/')
			count++;
		i++;
	}
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	count = 0;
	start = 0;
	while (token[i])
	{
		if (token[i] == '/')
		{
			if (i > start)
				result[count++] = ft_substr(token, start, i - start);
			start = i + 1;
		}
		i++;
	}
	if (i > start)
		result[count++] = ft_substr(token, start, i - start);
	result[count] = NULL;
	return (result);
}

static void	free_components(char **components)
{
	int	i;

	if (!components)
		return;
	i = 0;
	while (components[i])
	{
		free(components[i]);
		i++;
	}
	free(components);
}

static int	is_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0)
		return (S_ISDIR(st.st_mode));
	return (0);
}

static char	**append_trailing_slash(char **matches)
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

static char	**expand_wildcard_token(char *token)
{
	char	**components;
	char	**matches;
	char	*prefix;
	int		has_trailing_slash;

	if (!ft_strchr(token, '/'))
		return (expand_in_directory(".", token));
	has_trailing_slash = (token[ft_strlen(token) - 1] == '/');
	components = split_path_components(token);
	if (!components)
		return (NULL);
	prefix = (*token == '/') ? ft_strdup("/") : ft_strdup("");
	matches = expand_path_recursive(prefix, components, 0);
	free(prefix);
	free_components(components);
	if (has_trailing_slash && matches)
		matches = append_trailing_slash(matches);
	return (matches);
}

static char	**replace_token_with_matches(char **tokens, int idx, char **matches)
{
	char	**result;
	int		i;
	int		j;
	int		k;
	int		match_count;
	int		total;

	match_count = 0;
	while (matches && matches[match_count])
		match_count++;
	i = 0;
	while (tokens[i])
		i++;
	total = i - 1 + match_count;
	result = malloc(sizeof(char *) * (total + 1));
	if (!result)
		return (tokens);
	i = 0;
	k = 0;
	while (tokens[i])
	{
		if (i == idx)
		{
			j = 0;
			while (matches && matches[j])
				result[k++] = matches[j++];
			free(tokens[i]);
			if (matches)
				free(matches);
		}
		else
			result[k++] = tokens[i];
		i++;
	}
	result[k] = NULL;
	free(tokens);
	return (result);
}

char	**expand_wildcards(char **tokens)
{
	int		i;
	int		in_redirect;
	char	**matches;

	if (!tokens)
		return (NULL);
	i = 0;
	in_redirect = 0;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "<") || !ft_strcmp(tokens[i], ">")
			|| !ft_strcmp(tokens[i], "<<") || !ft_strcmp(tokens[i], ">>"))
		{
			in_redirect = 1;
			i++;
			continue ;
		}
		if (in_redirect)
		{
			in_redirect = 0;
			i++;
			continue ;
		}
		if (has_wildcard(tokens[i]))
		{
			matches = expand_wildcard_token(tokens[i]);
			if (matches && matches[0])
			{
				int	match_count = 0;
				while (matches[match_count])
					match_count++;
				tokens = replace_token_with_matches(tokens, i, matches);
				i += match_count;
			}
			else
			{
				if (matches)
					free(matches);
				i++;
			}
		}
		else
			i++;
	}
	return (tokens);
}
