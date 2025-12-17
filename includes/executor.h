/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:01:39 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/15 20:27:12 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "buildins.h"
# include "exit_status.h"
# include "minishell.h"
# include "utils.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

int		executor(t_node *nodes);
void	handle_redirections(t_node *node);
int		write_heredoc(t_node *node, int idx);
void	alloc_pipes(t_node *nodes);
void	free_pipes(t_node *nodes);
void	setup_pipe_fds(t_node *node, int cmd_index);
void	close_all_pipes(t_node *node);
int		is_executable_type(t_node_type type);
int		validate_infile(t_node *node);
int		validate_outfile(t_node *node);
void	wait_for_children(int cmd_count);
void	wait_and_set_status(pid_t pid);
void	execute_pipeline_child(t_node *node, int cmd_index);
int		execute_pipeline(t_node *nodes, int start);
int		find_matching_rpar(t_node *nodes, int start);
int		execute_subshell_group(t_node *nodes, int start);
int		execute_subshell_in_pipeline(t_node *nodes, int start, int cmd_idx);

#endif