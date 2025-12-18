/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set_inout.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:50:12 by zmin              #+#    #+#             */
/*   Updated: 2025/12/18 21:31:15 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

// check if it's redir and if so assign them number
// then check if next parameter if not redir
// assume it's file name or delimiter and set the value
static char	**parser_set_inout_exp(t_node *node, char **t, int *f)
{
	if (*t && (!ft_strncmp(*t, ">", 2) || !ft_strncmp(*t, "<", 2)
			|| !ft_strncmp(*t, ">>", 3) || !ft_strncmp(*t, "<<", 3)) && ++(*f))
	{
		if (!ft_strncmp(*t, "<", 2))
			node->in_flag = 1;
		else if (!ft_strncmp(*t, ">", 2))
			node->out_flag = 1;
		else if (!ft_strncmp(*t, "<<", 3))
			node->in_flag = 2;
		else if (!ft_strncmp(*t, ">>", 3))
			node->out_flag = 2;
		t++;
		if (*t && !ft_strchr("<|>", **t))
		{
			if (node->out_flag)
				append_outfile(node, *t);
			else if (node->in_flag == 1)
				append_infile(node, *t);
			else if (node->in_flag == 2)
				append_delimiter(node, *t);
		}
		if (*t)
			t++;
	}
	return (t);
}

// set infile, outfile, delimiter and type of redirect arrow
char	**parser_set_inout(t_node *node, char **tokens)
{
	int	flag;

	flag = 0;
	tokens = parser_set_inout_exp(node, tokens, &flag);
	if (flag)
		tokens = parser_set_inout(node, tokens);
	return (tokens);
}
