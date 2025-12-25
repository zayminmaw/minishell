/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:01:39 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 16:45:29 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "buildins.h"
# include "exit_status.h"
# include "minishell.h"
# include "utils.h"
# include <signal.h>
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
void		handle_execve_failure(t_node *node);
int		execute_subshell_group(t_node *nodes, int start);
int		execute_subshell_in_pipeline(t_node *nodes, int start, int cmd_idx);
int		wait_for_n_children(int n);
int		process_subshell_heredocs(t_node *nodes, int start, int end);
void		close_pipes_after_fork(t_node *node, int cmd_index);
void		redirect_middile_command(int **fd, t_node *node, int cmd_index);
int		execute_group(t_node *nodes, int start);
int		should_skip_execution(t_node_type pending_op, int status);
void		skip_command_group(t_node *nodes, int *i, t_node_type *pending_op);
int		handle_child_cmd(t_node *nodes, int *i, int *cmd_index, int total_cmds, pid_t *last_pid);
void		set_pipeline_last_pid(pid_t pid);
void		wait_for_children_with_last(int cmd_count, pid_t last_pid);

// heredoc_utils.c
char	*heredoc_tmpname(int idx);
char	*get_last_delimiter(t_node *node);
void	free_infiles(t_node *node);
int		set_heredoc_infile(t_node *node, char *tmp);
void	write_eof_warning(char *delimiter);

// subshell_aux.c

void	handle_subshell_dups(t_node *node, int **fd, int idx);
int		find_matching_rpar(t_node *nodes, int start);
void	wait_subshell_status(pid_t pid);
t_node	*get_sub_nodes(t_node *nodes, int start, int len, t_env *s_env);

#endif