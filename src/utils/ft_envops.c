/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:13:52 by zmin              #+#    #+#             */
/*   Updated: 2025/11/02 18:55:28 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	find_and_remove(int target_index, char **envp, char **envp_cpy)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (i != target_index)
		{
			envp_cpy[j] = ft_strdup(envp[i]);
			i++;
			j++;
		}
		else
			i++;
	}
}

// delete a variable from env
// target doesn't need =
// return a new memory allocated (2D) string
// if target is found or else if not found return original envp
char	**ft_delvar(char **envp, char *target)
{
	int		target_index;
	int		len;
	char	**envp_cpy;
	char	*full_target;

	full_target = ft_strjoin(target, "=");
	target_index = 0;
	while (envp[target_index])
	{
		if (ft_strncmp(envp[target_index], target, ft_strlen(target)) == 0)
			break ;
		target_index++;
	}
	if (envp[target_index] == NULL)
		return (free(full_target), envp);
	free(full_target);
	len = 0;
	while (envp[len])
		len++;
	envp_cpy = malloc(sizeof(char *) * len);
	envp_cpy[len - 1] = NULL;
	find_and_remove(target_index, envp, envp_cpy);
	ft_strarr_free(envp);
	return (envp_cpy);
}

// add new var to envp and return new memory
// allocated (2D) string
char	**ft_addvar(char **envp, char *var)
{
	int		i;
	int		len;
	char	**envp_cpy;

	len = 0;
	while (envp[len])
		len++;
	envp_cpy = malloc(sizeof(char *) * (len + 2));
	envp_cpy[len + 1] = NULL;
	i = 0;
	while (i < len)
	{
		envp_cpy[i] = ft_strdup(envp[i]);
		i++;
	}
	envp_cpy[i] = ft_strdup(var);
	ft_strarr_free(envp);
	return (envp_cpy);
}
