/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:15:12 by zmin              #+#    #+#             */
/*   Updated: 2025/12/18 20:26:29 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "minishell.h"
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/ioctl.h>

void	prompt(t_env *env);
void	set_prompt_signals(void);
void	set_execution_signals(void);
void	set_child_signals(void);
int		interpret_and_run(char *input, t_env *env);
char	**filter_empty_tokens(char **tokens);
void	clean_node_quotes(t_node *nodes, int node_len);
int		process_tokens(char **tokens, t_node **nodes, t_env *env);

#endif