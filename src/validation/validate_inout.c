/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_inout.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:03:52 by zmin              #+#    #+#             */
/*   Updated: 2025/12/18 20:58:41 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "validation.h"
#include "exit_status.h"
#include <unistd.h>

// check if token list is just "!" with no other tokens
// set exit status to 1 if true
// return 1 if bang only, 0 otherwise
static int	is_bang_only(char **tokens)
{
	if (!tokens || !tokens[0])
		return (0);
	if (!ft_strncmp(tokens[0], "!", 2) && !tokens[1])
	{
		set_exit_status(1);
		return (1);
	}
	return (0);
}

// validate if operator are followed by actual params
// return 0 if valid and 1 if not
int	validate_inout(char **tokens)
{
	if (!tokens || !tokens[0])
		return (0);
	if (is_bang_only(tokens))
		return (1);
	if (is_pipe(tokens[0]) || is_logical_op(tokens[0]))
		return (print_syntax_error(tokens[0]), 1);
	return (validate_tokens_loop(tokens));
}
