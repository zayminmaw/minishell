/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:03:07 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/11 19:10:55 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"
#include "exit_status.h"
#include "minishell.h"
#include "utils.h"

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
	if (ft_strcmp(node->full_cmd[0], "echo") == 0)
		set_exit_status(ft_echo(node));
	if (ft_strcmp(node->full_cmd[0], "pwd") == 0)
		set_exit_status(ft_pwd());
	if (ft_strcmp(node->full_cmd[0], "env") == 0)
		set_exit_status(ft_env(node->env->envp));
}

int	exec_buildin_parent(t_node *node)
{
	if (ft_strcmp(node->full_cmd[0], "unset") == 0)
		node->env->envp = ft_unset(node);
	else if (ft_strcmp(node->full_cmd[0], "cd") == 0)
		node->env->envp = ft_cd(node->env->envp, node->full_cmd);
	else if (ft_strcmp(node->full_cmd[0], "export") == 0)
		node->env->envp = ft_export(node->env->envp, node->full_cmd);
	else if (ft_strcmp(node->full_cmd[0], "exit") == 0)
		if (ft_exit(node))
			return (1);
	return (0);
}
