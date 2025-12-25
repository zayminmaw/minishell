/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:46:05 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/25 19:06:28 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// get the last infile from the infiles array
// returns NULL if no infiles or empty array
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

// get the last outfile from the outfiles array
// returns NULL if no outfiles or empty array
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

// handle input redirections: < filename or << delimiter
// only the last file is used for actual input
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

// handle output redirections: > or >>
// only the last file is used for actual output
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

// handle all redirections for a node
// processes input and output redirections
void	handle_redirections(t_node *node)
{
	handle_input_redirect(node);
	handle_output_redirect(node);
}
