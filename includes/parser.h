/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:19:50 by zmin              #+#    #+#             */
/*   Updated: 2025/11/25 20:01:21 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

t_node	*parser(char **tokens, t_env *env);
int		parser_count_tokens(char **tokens);
t_node	*parser_init_nodes(t_env *env);

#endif