/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:49:02 by zmin              #+#    #+#             */
/*   Updated: 2025/12/18 22:03:48 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

// lexer.c
int		lexer(char *input, t_env *env, char ***token);

// lexer_pad_str.c
char	*lexer_pad_str(char *input);

// lexer_tokenize.c
char	**lexer_tokenize(char *str);

// lexer_expand_var.c
char	*lexer_expand_var(char *token, char **envp);

// lexer_expand_utils.c
char	*join_and_free(char *s1, char *s2);
char	*get_var_value(char *var_name, char **envp);
char	*expand_var(char *s, int *i, char **envp);

// lexer_check_quote.c
int		lexer_check_quote(char **tokens);

// lexer_expand_wildcards.c
char	**expand_wildcards(char **tokens);

// lexer_wildcard_utils.c
int		has_wildcard(char *token);
char	*join_path(char *dir, char *name);
char	**add_match(char **matches, char *new_match, int *count);
void	free_components(char **components);
int		is_directory(char *path);

// lexer_wildcard_match.c
int		match_pattern(char *str, char *pattern);
char	**expand_in_directory(char *dir, char *pattern);

// lexer_wildcard_split.c
char	**split_path_components(char *token);
char	**append_trailing_slash(char **matches);

// lexer_wildcard_expand.c
char	**expand_path_recursive(char *prefix, char **components, int idx);
char	**expand_wildcard_token(char *token);

// lexer_wildcard_components.c
char	**handle_no_components(char *prefix);
char	**handle_no_wildcard_component(char *prefix, char **comp, int idx);

// lexer_wildcard_process.c
char	**process_wildcard_component(char *prefix, char **comp, int idx);

#endif