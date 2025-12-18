/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 21:00:00 by zmin              #+#    #+#             */
/*   Updated: 2025/12/18 20:58:41 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "validation.h"
#include "exit_status.h"
#include <unistd.h>

// check if token is surrounded by quotes
// return 1 if quoted, 0 otherwise
int	is_quoted(char *token)
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

// check if token is a redirection operator (>, >>, <, <<)
// return 1 if it's a redir, 0 otherwise
int	is_redir(char *token)
{
	if (!token || is_quoted(token))
		return (0);
	if (!ft_strncmp(token, ">>", 3) || !ft_strncmp(token, "<<", 3))
		return (1);
	if (!ft_strncmp(token, ">", 2) || !ft_strncmp(token, "<", 2))
		return (1);
	return (0);
}

// check if token is a pipe operator (|)
// return 1 if it's a pipe, 0 otherwise
int	is_pipe(char *token)
{
	if (!token || is_quoted(token))
		return (0);
	return (!ft_strncmp(token, "|", 2));
}

// check if token is a logical operator (&& or ||)
// return 1 if it's a logical op, 0 otherwise
int	is_logical_op(char *token)
{
	if (!token || is_quoted(token))
		return (0);
	if (!ft_strncmp(token, "&&", 3) || !ft_strncmp(token, "||", 3))
		return (1);
	return (0);
}

// check if token is an invalid operator (& or ;)
// return 1 if it's invalid, 0 otherwise
int	is_invalid_op(char *token)
{
	if (!token || is_quoted(token))
		return (0);
	if (!ft_strncmp(token, "&", 2) || !ft_strncmp(token, ";", 2))
		return (1);
	return (0);
}
