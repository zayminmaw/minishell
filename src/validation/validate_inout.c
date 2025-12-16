/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_inout.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:03:52 by zmin              #+#    #+#             */
/*   Updated: 2025/12/16 21:38:22 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "validation.h"
#include "exit_status.h"
#include <unistd.h>

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

static int	is_redir(char *token)
{
	if (!token || is_quoted(token))
		return (0);
	if (!ft_strncmp(token, ">>", 3) || !ft_strncmp(token, "<<", 3))
		return (1);
	if (!ft_strncmp(token, ">", 2) || !ft_strncmp(token, "<", 2))
		return (1);
	return (0);
}

static int	is_pipe(char *token)
{
	if (!token || is_quoted(token))
		return (0);
	return (!ft_strncmp(token, "|", 2));
}

static int	is_logical_op(char *token)
{
	if (!token || is_quoted(token))
		return (0);
	if (!ft_strncmp(token, "&&", 3) || !ft_strncmp(token, "||", 3))
		return (1);
	return (0);
}

static void	print_syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token)
		ft_putstr_fd(token, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
	set_exit_status(2);
}

// validate if operator are followed by actual params
// return 0 if valid and 1 if not. 
int	validate_inout(char **tokens)
{
	int	i;

	if (!tokens || !tokens[0])
		return (0);
	i = 0;
	if (is_pipe(tokens[0]))
		return (print_syntax_error(tokens[0]), 1);
	while (tokens[i])
	{
		if (is_redir(tokens[i]))
		{
			if (!tokens[i + 1] || is_pipe(tokens[i + 1])
				|| is_redir(tokens[i + 1]) || is_logical_op(tokens[i + 1]))
			{
				if (tokens[i + 1])
					print_syntax_error(tokens[i + 1]);
				else
					print_syntax_error(NULL);
				return (1);
			}
		}
		else if (is_pipe(tokens[i]))
		{
			if (!tokens[i + 1] || is_pipe(tokens[i + 1]))
			{
				if (tokens[i + 1])
					print_syntax_error(tokens[i + 1]);
				else
					print_syntax_error(tokens[i + 1]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}
