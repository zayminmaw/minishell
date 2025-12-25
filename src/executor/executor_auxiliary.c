/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_auxiliary.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:29:02 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 19:06:28 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <errno.h>

// check if node type is executable
// returns 1 for CMD and builtin types, 0 otherwise
int	is_executable_type(t_node_type type)
{
	return (type == CMD || type == BUILDIN_CHILD || type == BUILDIN_PARENT);
}

// process wait result and update status
// handles both exit and signal termination
static void	process_wait_result(int status, int *last, int *sigint_seen)
{
	int	sig;

	if (WIFEXITED(status))
		*last = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			*sigint_seen = 1;
		*last = 128 + sig;
	}
}

// wait for all child processes
// sets exit status based on last child or SIGINT
void	wait_for_children(int cmd_count)
{
	int		i;
	int		status;
	int		last_status;
	pid_t	ret;
	int		sigint_seen;

	i = 0;
	last_status = 0;
	sigint_seen = 0;
	while (i < cmd_count)
	{
		ret = waitpid(-1, &status, 0);
		if (ret == -1)
		{
			if (errno == EINTR)
				continue ;
			break ;
		}
		process_wait_result(status, &last_status, &sigint_seen);
		i++;
	}
	if (sigint_seen)
		set_exit_status(128 + SIGINT);
	else
		set_exit_status(last_status);
}

// wait for specific process and set exit status
// retries on EINTR signal interruption
void	wait_and_set_status(pid_t pid)
{
	int	status;

	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno != EINTR)
			return ;
	}
	if (WIFEXITED(status))
		set_exit_status(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		set_exit_status(128 + WTERMSIG(status));
}
