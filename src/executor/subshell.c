/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:59:33 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/09 20:38:35 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "utils.h"
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

static void	execute_subshell_child(t_node *nodes, int start, int end)
{
	t_env	sub_env;
	t_node	*sub_nodes;
	int		len;
	int		i;

	if (end <= start + 1)
		exit(0);
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
		execute_subshell_child(nodes, start, end);
	if (waitpid(pid, &status, 0) == -1)
		return (-1);
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
