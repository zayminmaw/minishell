/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_auxiliary.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:29:02 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 18:46:08 by zmin             ###   ########.fr       */
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
	int		i;
	int		status;
	int		last_status;
	pid_t	ret;
	int		sigint_seen;
	int		sig;

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
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
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
	int		count;
	int		status;
	int		last_status;
	pid_t	ret;
	int		sigint_seen;
	int		sig;

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
					continue ;
				break ;
			}
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if (sig == SIGINT)
					sigint_seen = 1;
				last_status = 128 + sig;
			}
			count = 1;
			break ;
		}
	}
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
			sigint_seen = 1;
		count++;
	}
	if (sigint_seen)
		set_exit_status(128 + SIGINT);
	else
		set_exit_status(last_status);
}
