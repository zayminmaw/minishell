/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_parens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:10:58 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 20:42:11 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include "minishell.h"
#include "utils.h"
#include <unistd.h>

static int	is_par(char *t, int check_left)
{
	if (check_left)
		return (t && t[0] == '(' && t[1] == '\0');
	return (t && t[0] == ')' && t[1] == '\0');
}

static int	is_valid_prev_for_lpar(char *prev)
{
	if (!prev)
		return (1);
	if (prev[0] == '(' && prev[1] == '\0')
		return (1);
	if (prev[0] == '|' && prev[1] == '\0')
		return (1);
	if (prev[0] == '&' && prev[1] == '\0')
		return (1);
	if (prev[0] == '&' && prev[1] == '&' && prev[2] == '\0')
		return (1);
	if (prev[0] == '|' && prev[1] == '|' && prev[2] == '\0')
		return (1);
	return (0);
}

static void	validate_parens_core(char **tokens, int *depth, char **prev, int i)
{
	if (is_par(tokens[i], 1))
	{
		if (!is_valid_prev_for_lpar(*prev))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `('\n",
				2);
			set_exit_status(2);
			*depth = -1;
			return ;
		}
		(*depth)++;
	}
	else if (is_par(tokens[i], 0))
	{
		if (*depth == 0)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `)'\n",
				2);
			set_exit_status(2);
			*depth = -1;
			return ;
		}
		(*depth)--;
	}
	*prev = tokens[i];
}

static int	has_double_open_parens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '(' && tokens[i][1] == '\0')
		{
			if (tokens[i + 1] && tokens[i + 1][0] == '(' && tokens[i
				+ 1][1] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	validate_parens(char **tokens)
{
	int		depth;
	int		i;
	char	*prev;

	depth = 0;
	prev = NULL;
	i = 0;
	while (tokens[i])
	{
		validate_parens_core(tokens, &depth, &prev, i);
		i++;
		if (depth == -1)
			return (1);
	}
	if (depth != 0)
	{
		print_error("syntax error", "unexpected end of file");
		return (set_exit_status(2), 1);
	}
	if (has_double_open_parens(tokens))
	{
		print_error("syntax error", "near unexpected token `((");
		return (set_exit_status(1), 1);
	}
	return (0);
}
