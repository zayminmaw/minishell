/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:30:00 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/24 21:27:17 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

char	*heredoc_tmpname(int idx)
{
	char	*num;
	char	*name;

	num = ft_itoa(idx);
	if (!num)
		return (NULL);
	name = ft_strjoin("/tmp/heredoc_", num);
	free(num);
	return (name);
}

char	*get_last_delimiter(t_node *node)
{
	int	i;

	if (!node->delimiters)
		return (NULL);
	i = 0;
	while (node->delimiters[i])
		i++;
	if (i == 0)
		return (NULL);
	return (node->delimiters[i - 1]);
}

void	free_infiles(t_node *node)
{
	int	i;

	if (!node->infiles)
		return ;
	i = 0;
	while (node->infiles[i])
	{
		free(node->infiles[i]);
		i++;
	}
	free(node->infiles);
}

int	set_heredoc_infile(t_node *node, char *tmp)
{
	node->infiles = malloc(sizeof(char *) * 2);
	if (node->infiles)
	{
		node->infiles[0] = tmp;
		node->infiles[1] = NULL;
		return (0);
	}
	free(tmp);
	return (1);
}

void	write_eof_warning(char *delimiter)
{
	write(2, "minishell: warning: here-document delimited by ", 48);
	write(2, "end-of-file (wanted `", 21);
	write(2, delimiter, ft_strlen(delimiter));
	write(2, "')\n", 3);
}
