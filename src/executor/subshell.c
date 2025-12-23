/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:59:33 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/21 03:21:30 by wmin-kha         ###   ########.fr       */
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

int	find_matching_rpar(t_node *nodes, int start)
{
	int	depth;
	int	j;

	depth = 1;
	j = start + 1;
	while (j < nodes->env->node_len && depth > 0)
	{
		if (nodes[j].type == L_PAR)
			depth++;
		else if (nodes[j].type == R_PAR)
			depth--;
		j++;
	}
	if (depth != 0)
		return (-1);
	return (j - 1);
}

static void	execute_subshell_child(t_node *nodes, int start, int end,
		int cmd_idx)
{
	t_env	sub_env;
	t_node	*sub_nodes;
	int		len;
	int		i;
	int		**fd;

	if (end <= start + 1)
		exit(0);
	if (cmd_idx >= 0)
	{
		fd = nodes[start].env->fd;
		if (fd)
		{
			if (cmd_idx == 0 && nodes[start].out_flag == 0)
			{
				if (dup2(fd[0][1], STDOUT_FILENO) < 0)
					ft_process_error(DUP_ERR, 1);
			}
			else if (cmd_idx == nodes[start].cmd_count - 1
				&& nodes[start].in_flag == 0)
			{
				if (dup2(fd[cmd_idx - 1][0], STDIN_FILENO) < 0)
					ft_process_error(DUP_ERR, 1);
			}
			else if (cmd_idx > 0 && cmd_idx < nodes[start].cmd_count - 1)
			{
				if (nodes[start].in_flag == 0)
				{
					if (dup2(fd[cmd_idx - 1][0], STDIN_FILENO) < 0)
						ft_process_error(DUP_ERR, 1);
				}
				if (nodes[start].out_flag == 0)
				{
					if (dup2(fd[cmd_idx][1], STDOUT_FILENO) < 0)
						ft_process_error(DUP_ERR, 1);
				}
			}
			i = 0;
			while (i < nodes[start].cmd_count - 1)
			{
				close(fd[i][0]);
				close(fd[i][1]);
				i++;
			}
		}
	}
	len = end - start - 1;
	sub_nodes = malloc(sizeof(t_node) * len);
	if (!sub_nodes)
		exit(1);
	sub_env = *(nodes[start].env);
	sub_env.node_len = len;
	sub_env.fd = NULL;
	sub_env.envp = ft_envcpy(nodes[start].env->envp);
	i = 0;
	while (i < len)
	{
		sub_nodes[i] = nodes[start + 1 + i];
		sub_nodes[i].env = &sub_env;
		i++;
	}
	parser_count_cmd(sub_nodes);
	set_child_signals();
	executor(sub_nodes);
	exit(get_exit_status());
}

int	execute_subshell_group(t_node *nodes, int start)
{
	int		end;
	pid_t	pid;
	int		status;
	int		sig;

	status = 0;
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
	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno != EINTR)
			return (-1);
	}
	if (WIFEXITED(status))
		set_exit_status(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			write(1, "Quit 3\n", 8);
		set_exit_status(128 + sig);
	}
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
