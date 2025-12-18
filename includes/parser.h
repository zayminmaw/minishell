/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:19:50 by zmin              #+#    #+#             */
/*   Updated: 2025/12/18 21:31:15 by zmin             ###   ########.fr       */
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
void	parser_count_cmd(t_node *nodes);
char	**expand_wildcards(char **tokens);
int		has_wildcard(char *token);
char	*join_path(char *dir, char *name);
char	**add_match(char **matches, char *new_match, int *count);
void	free_components(char **components);
int		is_directory(char *path);
int		match_pattern(char *str, char *pattern);
char	**expand_in_directory(char *dir, char *pattern);
char	**split_path_components(char *token);
char	**append_trailing_slash(char **matches);
char	**expand_path_recursive(char *prefix, char **components, int idx);
char	**expand_wildcard_token(char *token);
char	**handle_no_components(char *prefix);
char	**handle_no_wildcard_component(char *prefix, char **comp, int idx);
char	**process_match_recursive(char *match, char **comp, int idx,
			char **result);

int		count_array_elements(char **array);
char	**append_to_array(char **old_array, char *new_elem, int count);
void	append_infile(t_node *node, char *infile);
void	append_outfile(t_node *node, char *outfile);
void	append_delimiter(t_node *node, char *delimiter);

#endif