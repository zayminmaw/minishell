/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 21:11:06 by zmin              #+#    #+#             */
/*   Updated: 2025/12/02 01:49:15 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../libft/includes/libft.h"
# include "minishell.h"
# include <errno.h>
# include <stdio.h>
# include <string.h>

// ft_isenvempty
int		ft_isenvempty(char **str);

// ft_error.c
void	*ft_syntax_error(t_parse_error err_type, int exit_err_no);
void	*ft_process_error(t_process_error err_type, int exit_err_no);
void	*ft_file_error(t_file_error err_type, char *msg, int exit_err_no);
void	*ft_env_error(t_env_error err_type, char *msg, int exit_err_no);
void	ft_perror(char *prefix, char *arg);

// ft_envcpy.c
char	**ft_envcpy(char **envp);

// ft_envops.c
char	**ft_delvar(char **envp, char *target);
char	**ft_addvar(char **envp, char *var);

// ft_skipquotes.c
void	ft_skipquotes(char const *str, int *i);

// ft_validvarchar.c
int		ft_validvarchar(char c);

// ft_appendchar.c
char	*ft_appendchar(char *str, char c);

// ft_cleanquotes.c
char	*ft_cleanquotes(char *token);

// ft_getenv.c
char	*ft_getenv(char **envp, char *env_key);
char	**ft_get_pathenv(char **envp);

// ft_freeenv.c
void	ft_freeenv(t_env *env);

// ft_freenodes.c
void	ft_freenodes(t_node *nodes);

#endif