/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 21:11:06 by zmin              #+#    #+#             */
/*   Updated: 2025/11/04 21:58:52 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../libft/includes/libft.h"
# include "minishell.h"
# include <stdio.h>

// ft_isenvempty
int		ft_isenvempty(char **str);

// ft_error.c
void	*ft_parse_error(t_parse_error err_type, int exit_err_no);
void	*ft_process_error(t_process_error err_type, int exit_err_no);
void	*ft_file_error(t_file_error err_type, char *msg, int exit_err_no);
void	*ft_env_error(t_env_error err_type, char *msg, int exit_err_no);

// ft_envcpy.c
char	**ft_envcpy(char **envp);

// ft_envops.c
char	**ft_delvar(char **envp, char *target);
char	**ft_addvar(char **envp, char *var);

#endif