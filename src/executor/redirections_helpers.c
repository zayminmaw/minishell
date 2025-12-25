/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:45:45 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 15:48:11 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

char	*get_last_infile(t_node *node)
{
	int	i;

	if (!node->infiles)
		return (NULL);
	i = 0;
	while (node->infiles[i])
		i++;
	if (i == 0)
		return (NULL);
	return (node->infiles[i - 1]);
}

char	*get_last_outfile(t_node *node)
{
	int	i;

	if (!node->outfiles)
		return (NULL);
	i = 0;
	while (node->outfiles[i])
		i++;
	if (i == 0)
		return (NULL);
	return (node->outfiles[i - 1]);
}

static int	has_wildcard(char *str)
{
	if (!str)
		return (0);
	if (ft_strchr(str, '*'))
		return (1);
	return (0);
}

int	exec_has_wildcard(char *str)
{
	return (has_wildcard(str));
}

int	validate_outfile_entry(t_node *node, char *outfile, int out_flag)
{
	int	fd;
	int	flags;

	(void)node;
	if (has_wildcard(outfile))
		return (ft_file_error(AMBIGUOUS_ERR, outfile, 1), 1);
	flags = O_CREAT | O_WRONLY;
	if (out_flag == 1)
		flags |= O_TRUNC;
	else if (out_flag == 2)
		flags |= O_APPEND;
	fd = open(outfile, flags, 0644);
	if (fd < 0)
	{
		if (errno == ENOENT)
			return (ft_file_error(DIR_ERR, outfile, 1), 1);
		else if (errno == EACCES)
			return (ft_file_error(PERM_ERR, outfile, 1), 1);
		else if (errno == EISDIR)
			return (ft_file_error(ISDIR_ERR, outfile, 1), 1);
		else
			return (ft_file_error(PERM_ERR, outfile, 1), 1);
	}
	close(fd);
	return (0);
}
