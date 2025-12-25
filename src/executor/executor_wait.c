/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_wait.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 19:00:00 by zmin              #+#    #+#             */
/*   Updated: 2025/12/25 19:06:28 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <errno.h>

// process wait result for last_pid
// updates last status and sigint flag
static void	process_last_wait(int status, int *last, int *sigint_seen)
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

// wait for last_pid specifically and track status
// returns count of waited processes
static int	wait_for_last_pid(pid_t last_pid, int *last, int *sigint_seen)
{
	pid_t	ret;
	int		status;

	if (last_pid <= 0)
		return (0);
	while (1)
	{
		ret = waitpid(last_pid, &status, 0);
		if (ret == -1)
		{
			if (errno == EINTR)
				continue ;
			break ;
		}
		process_last_wait(status, last, sigint_seen);
		return (1);
	}
	return (0);
}

// wait for remaining children after last_pid
// tracks SIGINT signals from any child
static void	wait_remaining(int count, int cmd_count, int *sigint_seen)
{
	pid_t	ret;
	int		status;

	while (count < cmd_count)
	{
		ret = waitpid(-1, &status, 0);
		if (ret == -1)
		{
			if (errno == EINTR)
				continue ;
			break ;
		}
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			*sigint_seen = 1;
		count++;
	}
}

// wait for children with specific last process tracking
// sets exit status from last_pid or SIGINT
void	wait_for_children_with_last(int cmd_count, pid_t last_pid)
{
	int		count;
	int		last_status;
	int		sigint_seen;

	count = 0;
	last_status = 0;
	sigint_seen = 0;
	count = wait_for_last_pid(last_pid, &last_status, &sigint_seen);
	wait_remaining(count, cmd_count, &sigint_seen);
	if (sigint_seen)
		set_exit_status(128 + SIGINT);
	else
		set_exit_status(last_status);
}
