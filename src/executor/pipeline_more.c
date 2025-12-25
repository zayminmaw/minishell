/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_more.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:45:38 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 15:45:40 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <sys/stat.h>
#include <stdlib.h>

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

int	handle_child_cmd(t_node *nodes, int *i, int *cmd_index)
{
	pid_t	pid;

	if (nodes[*i].type == L_PAR)
		return (handle_par_child(nodes, i, cmd_index));
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
	close_pipes_after_fork(&nodes[*i], *cmd_index);
	(*cmd_index)++;
	(*i)++;
	return (0);
}
