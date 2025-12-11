/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_match.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:51:47 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/11 19:45:12 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

static int	cd_key_match(const char *entry, const char *key)
{
	size_t	len;

	len = ft_strlen(key);
	if (ft_strncmp(entry, key, len) != 0)
		return (0);
	if (entry[len] != '=')
		return (0);
	return (1);
}

char	*cd_getenv_value(char **env, const char *key)
{
	int		i;
	size_t	len;

	if (!env || !key)
		return (NULL);
	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (cd_key_match(env[i], key))
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	**cd_setenv_value(char **env, const char *key, const char *value)
{
	char	*tmp;
	char	*var;
	int		i;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (env);
	var = ft_strjoin(tmp, value);
	free(tmp);
	if (!var)
		return (env);
	i = 0;
	while (env && env[i])
	{
		if (cd_key_match(env[i], key))
		{
			free(env[i]);
			env[i] = var;
			return (env);
		}
		i++;
	}
	env = ft_addvar(env, var);
	free(var);
	return (env);
}
