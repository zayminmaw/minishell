/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:49:19 by zmin              #+#    #+#             */
/*   Updated: 2025/12/11 19:10:25 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDINS_H
# define BUILDINS_H

# include "minishell.h"

// buildins.c
int		is_buildin(char *cmd);
int		is_parent_buildin(char *cmd);
void	exec_buildin_child(t_node *node);
int		exec_buildin_parent(t_node *node);

// ft_echo.c
int		ft_echo(t_node *node);

// ft_pwd.c
int		ft_pwd(void);

// ft_env.c
int		ft_env(char **env);

// ft_exit.c
int		ft_exit(t_node *node);

// ft_unset.c
char	**ft_unset(t_node *node);

// ft_export.c
char	**ft_export(char **env, char **full_cmd);

// ft_cd.c
char	**ft_cd(char **env, char **full_cmd);

typedef enum e_cd_error
{
	HOME_NOT_SET,
	OLDPWD,
	TOO_MANY,
	PATH
}		t_cd_error;

#endif