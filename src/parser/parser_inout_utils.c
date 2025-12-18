/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_inout_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:15:00 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/18 21:31:15 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

// count existing array elements
int	count_array_elements(char **array)
{
	int	count;

	count = 0;
	if (array)
	{
		while (array[count])
			count++;
	}
	return (count);
}

// copy old array to new array and add new element
// return new array with added element
char	**append_to_array(char **old_array, char *new_elem, int count)
{
	char	**new_array;
	int		i;

	new_array = malloc(sizeof(char *) * (count + 2));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_array[i] = old_array[i];
		i++;
	}
	new_array[count] = ft_strdup(new_elem);
	if (!new_array[count])
	{
		free(new_array);
		return (NULL);
	}
	new_array[count + 1] = NULL;
	return (new_array);
}

// append infile to the infiles array
void	append_infile(t_node *node, char *infile)
{
	char	**new_infiles;
	int		count;

	if (!infile)
		return ;
	count = count_array_elements(node->infiles);
	new_infiles = append_to_array(node->infiles, infile, count);
	if (!new_infiles)
		return ;
	if (node->infiles)
		free(node->infiles);
	node->infiles = new_infiles;
}

// append outfile to the outfiles array
void	append_outfile(t_node *node, char *outfile)
{
	char	**new_outfiles;
	int		count;

	if (!outfile)
		return ;
	count = count_array_elements(node->outfiles);
	new_outfiles = append_to_array(node->outfiles, outfile, count);
	if (!new_outfiles)
		return ;
	if (node->outfiles)
		free(node->outfiles);
	node->outfiles = new_outfiles;
}

// append delimiter to the delimiters array
void	append_delimiter(t_node *node, char *delimiter)
{
	char	**new_delimiters;
	int		count;

	if (!delimiter)
		return ;
	count = count_array_elements(node->delimiters);
	new_delimiters = append_to_array(node->delimiters, delimiter, count);
	if (!new_delimiters)
		return ;
	if (node->delimiters)
		free(node->delimiters);
	node->delimiters = new_delimiters;
}
