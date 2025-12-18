/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 21:10:00 by zmin              #+#    #+#             */
/*   Updated: 2025/12/18 20:58:41 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "validation.h"
#include "exit_status.h"
#include <unistd.h>

// print syntax error message with the problematic token
// set exit status to 2
void	print_syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token)
		ft_putstr_fd(token, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
	set_exit_status(2);
}

// validate redirection followed by valid token
// check if next token exists and is not an operator
// return 1 if error, 0 if valid
int	validate_redir_next(char **tokens, int i)
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
	return (0);
}

// validate pipe or logical operator followed by valid token
// check if next token exists and is not another pipe/logical op
// return 1 if error, 0 if valid
int	validate_pipe_logic_next(char **tokens, int i)
{
	if (!tokens[i + 1] || is_pipe(tokens[i + 1])
		|| is_logical_op(tokens[i + 1]))
	{
		if (tokens[i + 1])
			print_syntax_error(tokens[i + 1]);
		else
			print_syntax_error(tokens[i + 1]);
		return (1);
	}
	return (0);
}

// validate each token in the array
// check for invalid operators, redirections, pipes, and logical operators
// return 1 if error found, 0 if valid
int	validate_tokens_loop(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_invalid_op(tokens[i]))
			return (print_syntax_error(tokens[i]), 1);
		if (is_redir(tokens[i]))
		{
			if (validate_redir_next(tokens, i))
				return (1);
		}
		else if (is_pipe(tokens[i]) || is_logical_op(tokens[i]))
		{
			if (validate_pipe_logic_next(tokens, i))
				return (1);
		}
		i++;
	}
	return (0);
}
