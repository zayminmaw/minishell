/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:19:50 by zmin              #+#    #+#             */
/*   Updated: 2025/11/29 14:33:36 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

t_node	*parser(char **tokens, t_env *env);
int		parser_count_nodes(char **tokens);
t_node	*parser_init_nodes(t_env *env);
char	**parser_build_nodes(t_node *node, char **tokens, char **envp);
char	**parser_set_inout(t_node *node, char **tokens);
int		parser_resolve_nodes(char *token, t_node *node);
char	*parser_build_path(char **envp, char *path);
int		parser_count_args(char **tokens);
char	**parser_set_fullcmd(t_node *node, int args_count, char **tokens);

#endif