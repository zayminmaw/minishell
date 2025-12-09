/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:23:24 by zmin              #+#    #+#             */
/*   Updated: 2025/12/09 22:12:56 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"
#include "exit_status.h"
#include "utils.h"

static int	is_valid_varname(char *s)
{
	int	i;

	i = 1;
	if (s[0] == '_' && s[1] && s[1] == '=')
		return (3);
	if (!s || !(ft_isalpha(s[0])))
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (!(ft_isalnum(s[i])) || s[i] == '-')
			return (1);
		i++;
	}
	return (2);
}

static void	update_or_add(char ***env, char *arg)
{
	int		i;
	char	*key;
	int		key_len;

	key_len = 0;
	while (arg[key_len] && arg[key_len] != '=')
		key_len++;
	key = ft_substr(arg, 0, key_len);
	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], key, key_len)
            && (*env)[i][key_len] == '=')
        {
            free((*env)[i]);
            (*env)[i] = ft_strdup(arg);
            free(key);
            return ;
        }
		i++;
	}
	*env = ft_addvar(*env, arg);
	free(key);
}

char	**ft_export(char **env, char **full_cmd)
{
	int		i;

	if (!full_cmd[1])
		return (env);
	i = 1;
	while (full_cmd[i])
	{
		if (is_valid_varname(full_cmd[i]) == 0)
		{
			printf("minishell: export: not an identifier: %s\n", full_cmd[i]);
			set_exit_status(1);
		}
		else if (is_valid_varname(full_cmd[i]) == 1)
		{
			printf("minishell: export: not valid in this context: %s\n", full_cmd[i]);
			set_exit_status(1);
		}
		else if (is_valid_varname(full_cmd[i]) == 2)
		{
			update_or_add(&env, full_cmd[i]);
			set_exit_status(0);
		}
		i++;
	}
	return (env);
}
