/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 19:11:38 by zmin              #+#    #+#             */
/*   Updated: 2025/11/27 20:29:14 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_getenv(char **envp, char *env_key)
{
	int	i;
	int	key_len;

	key_len = ft_strlen(env_key);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], env_key, key_len) && envp[i][key_len] == '=')
			return (envp[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

char	**ft_get_pathenv(char **envp)
{
	return (ft_split(ft_getenv(envp, "PATH"), ':'));
}
