/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_set_inout.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:50:12 by zmin              #+#    #+#             */
/*   Updated: 2025/12/18 17:11:21 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

// append infile to the infiles array
static void	append_infile(t_node *node, char *infile)
{
	char	**new_infiles;
	int		count;
	int		i;

	if (!infile)
		return ;
	count = 0;
	if (node->infiles)
	{
		while (node->infiles[count])
			count++;
	}
	new_infiles = malloc(sizeof(char *) * (count + 2));
	if (!new_infiles)
		return ;
	i = 0;
	while (i < count)
	{
		new_infiles[i] = node->infiles[i];
		i++;
	}
	new_infiles[count] = ft_strdup(infile);
	if (!new_infiles[count])
	{
		free(new_infiles);
		return ;
	}
	new_infiles[count + 1] = NULL;
	if (node->infiles)
		free(node->infiles);
	node->infiles = new_infiles;
}

// append outfile to the outfiles array
static void	append_outfile(t_node *node, char *outfile)
{
	char	**new_outfiles;
	int		count;
	int		i;

	if (!outfile)
		return ;
	count = 0;
	if (node->outfiles)
	{
		while (node->outfiles[count])
			count++;
	}
	new_outfiles = malloc(sizeof(char *) * (count + 2));
	if (!new_outfiles)
		return ;
	i = 0;
	while (i < count)
	{
		new_outfiles[i] = node->outfiles[i];
		i++;
	}
	new_outfiles[count] = ft_strdup(outfile);
	if (!new_outfiles[count])
	{
		free(new_outfiles);
		return ;
	}
	new_outfiles[count + 1] = NULL;
	if (node->outfiles)
		free(node->outfiles);
	node->outfiles = new_outfiles;
}

// append delimiter to the delimiters array
static void	append_delimiter(t_node *node, char *delimiter)
{
	char	**new_delimiters;
	int		count;
	int		i;

	if (!delimiter)
		return ;
	count = 0;
	if (node->delimiters)
	{
		while (node->delimiters[count])
			count++;
	}
	new_delimiters = malloc(sizeof(char *) * (count + 2));
	if (!new_delimiters)
		return ;
	i = 0;
	while (i < count)
	{
		new_delimiters[i] = node->delimiters[i];
		i++;
	}
	new_delimiters[count] = ft_strdup(delimiter);
	if (!new_delimiters[count])
	{
		free(new_delimiters);
		return ;
	}
	new_delimiters[count + 1] = NULL;
	if (node->delimiters)
		free(node->delimiters);
	node->delimiters = new_delimiters;
}

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
