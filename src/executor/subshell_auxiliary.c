/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_auxiliary.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:33:43 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/24 21:36:33 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	handle_subshell_dups(t_node *node, int **fd, int idx)
{
	if (idx == 0 && node->out_flag == 0)
	{
		if (dup2(fd[0][1], STDOUT_FILENO) < 0)
			ft_process_error(DUP_ERR, 1);
	}
	else if (idx == node->cmd_count - 1 && node->in_flag == 0)
	{
		if (dup2(fd[idx - 1][0], STDIN_FILENO) < 0)
			ft_process_error(DUP_ERR, 1);
	}
	else if (idx > 0 && idx < node->cmd_count - 1)
	{
		if (node->in_flag == 0 && dup2(fd[idx - 1][0], STDIN_FILENO) < 0)
			ft_process_error(DUP_ERR, 1);
		if (node->out_flag == 0 && dup2(fd[idx][1], STDOUT_FILENO) < 0)
			ft_process_error(DUP_ERR, 1);
	}
}

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

void	wait_subshell_status(pid_t pid)
{
	int	status;
	int	sig;

	status = 0;
	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno != EINTR)
			return ;
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
}

t_node	*get_sub_nodes(t_node *nodes, int start, int len, t_env *s_env)
{
	t_node	*sub_nodes;
	int		i;

	sub_nodes = malloc(sizeof(t_node) * len);
	if (!sub_nodes)
		exit(1);
	*s_env = *(nodes[start].env);
	s_env->node_len = len;
	s_env->fd = NULL;
	s_env->envp = ft_envcpy(nodes[start].env->envp);
	i = 0;
	while (i < len)
	{
		sub_nodes[i] = nodes[start + 1 + i];
		sub_nodes[i].env = s_env;
		i++;
	}
	return (sub_nodes);
}
