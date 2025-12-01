/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:03:07 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/01 20:21:37 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"
#include "minishell.h"
#include "utils.h"
#include "exit_status.h"

int	is_buildin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	return (0);
}

int	is_parent_buildin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	exec_buildin_child(t_node *node)
{
	if (!ft_strcmp(node->full_cmd[0], "echo"))
		set_exit_status(ft_echo(node));
	if (!ft_strcmp(node->full_cmd[0], "pwd"))
		set_exit_status(ft_pwd());
	if (!ft_strcmp(node->full_cmd[0], "env"))
		set_exit_status(ft_env(node->env->envp));
	// printf("minishell: %s: buildin not implemented yet\n", node->full_cmd[0]);
	exit(0);
}

int	exec_buildin_parent(t_node *node)
{
	printf("minishell: %s: buildin not implemented yet\n", node->full_cmd[0]);
	return (0);
}
