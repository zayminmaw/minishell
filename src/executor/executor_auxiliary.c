/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_auxiliary.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:29:02 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 16:45:29 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <errno.h>

int	is_executable_type(t_node_type type)
{
	return (type == CMD || type == BUILDIN_CHILD || type == BUILDIN_PARENT);
}

void	wait_for_children(int cmd_count)
{
	int	i;
	int	status;
	int	last_status;
	pid_t	ret;
	int	sigint_seen;

	i = 0;
	last_status = 0;
	sigint_seen = 0;
	while (i < cmd_count)
	{
		ret = waitpid(-1, &status, 0);
		if (ret == -1)
		{
			if (errno == EINTR)
				continue;
			break;
		}
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			int sig = WTERMSIG(status);
			if (sig == SIGINT)
				sigint_seen = 1;
			last_status = 128 + sig;
		}
		i++;
	}
	if (sigint_seen)
		set_exit_status(128 + SIGINT);
	else
		set_exit_status(last_status);
}

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

void	wait_for_children_with_last(int cmd_count, pid_t last_pid)
{
	int	count;
	int	status;
	int	last_status;
	pid_t	ret;
	int	sigint_seen;

	count = 0;
	last_status = 0;
	sigint_seen = 0;
	if (last_pid > 0)
	{
		while (1)
		{
			ret = waitpid(last_pid, &status, 0);
			if (ret == -1)
			{
				if (errno == EINTR)
					continue;
				break;
			}
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				int sig = WTERMSIG(status);
				if (sig == SIGINT)
					sigint_seen = 1;
				last_status = 128 + sig;
			}
			count = 1;
			break;
		}
	}
	while (count < cmd_count)
	{
		ret = waitpid(-1, &status, 0);
		if (ret == -1)
		{
			if (errno == EINTR)
				continue;
			break;
		}
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			sigint_seen = 1;
		count++;
	}
	if (sigint_seen)
		set_exit_status(128 + SIGINT);
	else
		set_exit_status(last_status);
}
