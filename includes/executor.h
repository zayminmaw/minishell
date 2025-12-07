/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:01:39 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/04 00:06:30 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

int		executor(t_node *nodes);
void	handle_redirections(t_node *node);
void	write_heredoc(t_node *node);
void	alloc_pipes(t_node *nodes);
void	free_pipes(t_node *nodes);
void	setup_pipe_fds(t_node *node, int cmd_index);
void	close_all_pipes(t_node *node);

#endif