/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:45:45 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 19:06:28 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

// check if a string contains unquoted wildcards
// returns 1 if wildcards are found, 0 otherwise
static int	has_wildcard(char *str)
{
	if (!str)
		return (0);
	if (ft_strchr(str, '*'))
		return (1);
	return (0);
}

// validate ALL input files (not just the last one)
// bash checks all files even if only the last is used
int	validate_infile(t_node *node)
{
	int	i;

	if (node->in_flag != 1)
		return (0);
	if (!node->infiles)
		return (0);
	i = 0;
	while (node->infiles[i])
	{
		if (has_wildcard(node->infiles[i]))
			return (ft_file_error(AMBIGUOUS_ERR, node->infiles[i], 1), 1);
		if (access(node->infiles[i], F_OK) < 0)
			return (ft_file_error(DIR_ERR, node->infiles[i], 1), 1);
		if (access(node->infiles[i], R_OK) < 0)
			return (ft_file_error(PERM_ERR, node->infiles[i], 1), 1);
		i++;
	}
	return (0);
}

// validate single outfile entry
// opens file to check permissions and create/truncate
static int	validate_outfile_entry(char *outfile, int out_flag)
{
	int	fd;
	int	flags;

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

// validate and open ALL output files (not just the last one)
// bash opens all files to check permissions and create/truncate them
// this matches bash behavior exactly
int	validate_outfile(t_node *node)
{
	int	i;

	if (node->out_flag == 0 || !node->outfiles)
		return (0);
	i = 0;
	while (node->outfiles[i])
	{
		if (validate_outfile_entry(node->outfiles[i], node->out_flag))
			return (1);
		i++;
	}
	return (0);
}
