/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_build_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 19:15:58 by zmin              #+#    #+#             */
/*   Updated: 2025/11/27 20:15:55 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

static int	count_slash(char *path)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (path[i])
	{
		if (path[i] == '/')
			count++;
		i++;
	}
	return (count);
}

static char	*construct_path(char **envp, char *token)
{
	int		i;
	char	**env_path;
	char	*path;
	char	*path_and_cmd;

	env_path = ft_get_pathenv(envp);
	i = 0;
	while (env_path[i])
	{
		path = ft_strjoin(env_path[i++], "/");
		path_and_cmd = ft_strjoin(path, token);
		free(path);
		if (access(path_and_cmd, F_OK) == 0)
		{
			ft_strarr_free(env_path);
			return (path_and_cmd);
		}
		free(path_and_cmd);
	}
	if (env_path)
		ft_strarr_free(env_path);
	return (NULL);
}

char	*parser_build_path(char **envp, char *token)
{
	if (count_slash(token) > 0 && !access(token, F_OK))
		return (ft_strdup(token));
	else if (count_slash(token) == 0)
		return (construct_path(envp, token));
	return (NULL);
}
