/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 20:49:19 by zmin              #+#    #+#             */
/*   Updated: 2025/12/01 19:37:51 by zmin             ###   ########.fr       */
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

// ft_echo
int	ft_echo(t_node *node);

#endif