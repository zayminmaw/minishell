/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_auxiliary.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:29:02 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/08 21:01:15 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

int	is_executable_type(t_node_type type)
{
	return (type == CMD || type == BUILDIN_CHILD || type == BUILDIN_PARENT);
}

void	wait_for_children(int cmd_count)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	while (i < cmd_count)
	{
		wait(&status);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		i++;
	}
	set_exit_status(last_status);
}

void	wait_and_set_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		set_exit_status(WEXITSTATUS(status));
}
