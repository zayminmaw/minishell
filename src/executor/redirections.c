/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:46:05 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/22 21:32:43 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/*
** Get the last infile from the infiles array
*/
static char	*get_last_infile(t_node *node)
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

/*
** Get the last outfile from the outfiles array
*/
static char	*get_last_outfile(t_node *node)
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

/*
** Handle input redirections: < filename or << delimiter
** Only the last file is used for actual input
*/
static void	handle_input_redirect(t_node *node)
{
	int		fd;
	char	*infile;

	if (node->in_flag == 0)
		return ;
	infile = get_last_infile(node);
	if (!infile)
		return ;
	fd = open(infile, O_RDONLY);
	if (fd < 0)
	{
		ft_perror(NULL, infile);
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		ft_process_error(DUP_ERR, 1);
	close(fd);
	if (node->in_flag == 2)
		unlink(infile);
}

/*
** Handle output redirections: > or >>
** Only the last file is used for actual output
*/
static void	handle_output_redirect(t_node *node)
{
	int		fd;
	int		flags;
	char	*outfile;

	if (node->out_flag == 0)
		return ;
	outfile = get_last_outfile(node);
	if (!outfile)
		return ;
	flags = O_CREAT | O_WRONLY;
	if (node->out_flag == 1)
		flags |= O_TRUNC;
	else if (node->out_flag == 2)
		flags |= O_APPEND;
	fd = open(outfile, flags, 0644);
	if (fd < 0)
	{
		ft_perror(NULL, outfile);
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
		ft_process_error(DUP_ERR, 1);
	close(fd);
}

void	handle_redirections(t_node *node)
{
	handle_input_redirect(node);
	handle_output_redirect(node);
}

/*
** Check if a string contains unquoted wildcards
** Returns 1 if wildcards are found, 0 otherwise
*/
static int	has_wildcard(char *str)
{
	if (!str)
		return (0);
	if (ft_strchr(str, '*'))
		return (1);
	return (0);
}

/*
** Validate ALL input files (not just the last one)
** Bash checks all files even if only the last is used
*/
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

/*
** Validate and open ALL output files (not just the last one)
** Bash opens all files to check permissions and create/truncate them
** This matches bash behavior exactly
*/
int	validate_outfile(t_node *node)
{
	int	i;
	int	fd;
	int	flags;

	if (node->out_flag == 0 || !node->outfiles)
		return (0);
	i = 0;
	while (node->outfiles[i])
	{
		if (has_wildcard(node->outfiles[i]))
			return (ft_file_error(AMBIGUOUS_ERR, node->outfiles[i], 1), 1);
		flags = O_CREAT | O_WRONLY;
		if (node->out_flag == 1)
			flags |= O_TRUNC;
		else if (node->out_flag == 2)
			flags |= O_APPEND;
		fd = open(node->outfiles[i], flags, 0644);
		if (fd < 0)
		{
			if (errno == ENOENT)
				return (ft_file_error(DIR_ERR, node->outfiles[i], 1), 1);
			else if (errno == EACCES)
				return (ft_file_error(PERM_ERR, node->outfiles[i], 1), 1);
			else if (errno == EISDIR)
				return (ft_file_error(ISDIR_ERR, node->outfiles[i], 1), 1);
			else
				return (ft_file_error(PERM_ERR, node->outfiles[i], 1), 1);
		}
		close(fd);
		i++;
	}
	return (0);
}
