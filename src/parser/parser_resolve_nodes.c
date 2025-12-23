/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resolve_nodes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:12:11 by zmin              #+#    #+#             */
/*   Updated: 2025/12/18 21:31:15 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

// check if token is surrounded by quotes
static int	is_quoted(char *token)
{
	int	len;

	if (!token || !token[0])
		return (0);
	len = ft_strlen(token);
	if (len >= 2 && (token[0] == '\'' || token[0] == '"'))
	{
		if (token[len - 1] == token[0])
			return (1);
	}
	return (0);
}

// check if token is an operator and set node type
// return 1 if operator found, 0 otherwise
static int	check_operators(char *token, t_node *node)
{
	if (!ft_strcmp(token, "&&"))
		node->type = DOUBLE_AND;
	else if (!ft_strcmp(token, "||"))
		node->type = DOUBLE_OR;
	else if (!ft_strcmp(token, "|"))
		node->type = PIPE;
	else if (!ft_strcmp(token, "("))
		node->type = L_PAR;
	else if (!ft_strcmp(token, ")"))
		node->type = R_PAR;
	if (node->type != ALIEN)
		return (1);
	return (0);
}

// Return 1 -> buildin commands
// Return 2 -> operator
// Return 0 -> normal commands
int	parser_resolve_nodes(char *token, t_node *node)
{
	if (!token)
		return (1);
	if (!ft_strcmp(token, "export") || !ft_strcmp(token, "cd")
		|| !ft_strcmp(token, "unset") || !ft_strcmp(token, "exit")
		|| !ft_strcmp(token, "."))
		return (node->type = BUILDIN_PARENT, 1);
	else if (!ft_strcmp(token, "echo") || !ft_strcmp(token, "pwd")
		|| !ft_strcmp(token, "env"))
		return (node->type = BUILDIN_CHILD, 1);
	if (is_quoted(token))
	{
		node->type = CMD;
		return (0);
	}
	if (check_operators(token, node))
		return (2);
	node->type = CMD;
	return (0);
}
