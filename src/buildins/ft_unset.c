/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zayminmaw <zayminmaw@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:49:09 by zmin              #+#    #+#             */
/*   Updated: 2025/12/11 17:42:24 by zayminmaw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"
#include "exit_status.h"
#include "utils.h"

char	**ft_unset(t_node *node)
{
	char	**new_envp;
	int		i;

	i = 1;
	new_envp = node->env->envp;
	while (node->full_cmd[i])
	{
		new_envp = ft_delvar(new_envp, node->full_cmd[i]);
		i++;
	}
	set_exit_status(0);
	return (new_envp);
}
