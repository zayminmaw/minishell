/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:59:33 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/24 21:37:39 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "parser.h"
#include "prompt.h"
#include "utils.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

static void	handle_subshell_pipes(t_node *nodes, int start, int cmd_idx)
{
	int	i;
	int	**fd;

	if (cmd_idx < 0 || !nodes[start].env->fd)
		return ;
	fd = nodes[start].env->fd;
	handle_subshell_dups(&nodes[start], fd, cmd_idx);
	i = 0;
	while (i < nodes[start].cmd_count - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

static void	execute_subshell_child(t_node *nodes, int start, int end, int idx)
{
	t_env	sub_env;
	t_node	*sub_nodes;

	if (end <= start + 1)
		exit(0);
	handle_subshell_pipes(nodes, start, idx);
	sub_nodes = get_sub_nodes(nodes, start, end - start - 1, &sub_env);
	parser_count_cmd(sub_nodes);
	set_child_signals();
	executor(sub_nodes);
	exit(get_exit_status());
}

int	execute_subshell_group(t_node *nodes, int start)
{
	int		end;
	pid_t	pid;

	end = find_matching_rpar(nodes, start);
	if (end < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		ft_process_error(FORK_ERR, 1);
		return (-1);
	}
	if (pid == 0)
		execute_subshell_child(nodes, start, end, -1);
	wait_subshell_status(pid);
	return (end + 1);
}

int	execute_subshell_in_pipeline(t_node *nodes, int start, int cmd_idx)
{
	int		end;
	pid_t	pid;

	end = find_matching_rpar(nodes, start);
	if (end < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		ft_process_error(FORK_ERR, 1);
		return (-1);
	}
	if (pid == 0)
		execute_subshell_child(nodes, start, end, cmd_idx);
	return (end + 1);
}
