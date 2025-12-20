/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_parens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:10:58 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/21 03:07:13 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include "minishell.h"
#include "utils.h"
#include <unistd.h>

static int	is_lpar(char *t)
{
	return (t && t[0] == '(' && t[1] == '\0');
}

static int	is_rpar(char *t)
{
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
	if (is_lpar(tokens[i]))
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
	else if (is_rpar(tokens[i]))
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
		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
		set_exit_status(2);
		return (1);
	}
	return (0);
}
