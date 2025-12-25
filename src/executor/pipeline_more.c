/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_more.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:45:38 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 19:06:28 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <sys/stat.h>
#include <stdlib.h>

// handle subshell in pipeline
// processes heredocs and executes subshell child
static int	handle_par_child(t_node *nodes, int *i, int *cmd_index)
{
	int	env_end;
	int	next_i;

	env_end = find_matching_rpar(nodes, *i);
	if (env_end < 0)
		return (-1);
	if (process_subshell_heredocs(nodes, *i, env_end) < 0)
		return (-1);
	next_i = execute_subshell_in_pipeline(nodes, *i, *cmd_index);
	if (next_i < 0)
		return (-1);
	close_pipes_after_fork(&nodes[*i], *cmd_index);
	(*cmd_index)++;
	*i = next_i;
	return (0);
}

// execute child command in pipeline
// handles heredoc, fork, and pipe cleanup
static int	exec_cmd_child(t_node *nodes, int *i, int *cmd_index, pid_t *last)
{
	pid_t	pid;
	int		total_cmds;

	total_cmds = nodes[*i].cmd_count;
	if (write_heredoc(&nodes[*i], *i))
		return (1);
	pid = fork();
	if (pid < 0)
	{
		ft_process_error(FORK_ERR, 1);
		return (-1);
	}
	if (pid == 0)
		execute_pipeline_child(&nodes[*i], *cmd_index);
	if (pid > 0 && last && *cmd_index == total_cmds - 1)
		*last = pid;
	close_pipes_after_fork(&nodes[*i], *cmd_index);
	(*cmd_index)++;
	(*i)++;
	return (0);
}

// handle child command or subshell in pipeline
// routes to appropriate handler based on node type
int	handle_child_cmd(t_node *nodes, int *i, int *cmd_index, pid_t *last)
{
	if (nodes[*i].type == L_PAR)
		return (handle_par_child(nodes, i, cmd_index));
	return (exec_cmd_child(nodes, i, cmd_index, last));
}
