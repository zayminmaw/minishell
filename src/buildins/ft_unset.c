/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:49:09 by zmin              #+#    #+#             */
/*   Updated: 2025/12/06 17:54:26 by zmin             ###   ########.fr       */
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
	while (node->full_cmd[i])
	{
		new_envp = ft_delvar(node->env->envp, node->full_cmd[i]);
		i++;
	}
	set_exit_status(0);
	return (new_envp);
}
