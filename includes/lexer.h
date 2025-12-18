/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:49:02 by zmin              #+#    #+#             */
/*   Updated: 2025/12/18 20:47:40 by zmin             ###   ########.fr       */
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

#endif