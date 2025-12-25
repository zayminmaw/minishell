/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:42:15 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 15:42:19 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <sys/stat.h>
#include <stdlib.h>

void	handle_execve_failure(t_node *node)
{
	struct stat	path_stat;

	if (ft_strchr(node->full_cmd[0], '/'))
	{
		if (stat(node->full_cmd[0], &path_stat) == 0)
		{
			if (S_ISDIR(path_stat.st_mode))
			{
				ft_file_error(ISDIR_ERR, node->full_cmd[0], 126);
				exit(126);
			}
			ft_file_error(PERM_ERR, node->full_cmd[0], 126);
			exit(126);
		}
		ft_file_error(DIR_ERR, node->full_cmd[0], 127);
	}
	else
		ft_file_error(CMD_ERR, node->full_cmd[0], 127);
	exit(127);
}
