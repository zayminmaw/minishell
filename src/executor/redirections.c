/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:46:05 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/17 15:23:15 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>

/*
** Handle input redirections: < filename
**
** Files are pre-validated in parent process.
** Here we just open and redirect.
*/
static void	handle_input_redirect(t_node *node)
{
	int	fd;

	if (node->in_flag == 0)
		return ;
	if (!node->infile)
		return ;
	if (node->in_flag == 1)
		fd = open(node->infile, O_RDONLY);
	else
		fd = open(node->infile, O_RDONLY);
	if (fd < 0)
	{
		if (node->in_flag == 1)
			ft_perror(NULL, node->infile);
		else
			ft_perror("open here", node->infile);
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		ft_process_error(DUP_ERR, 1);
	close(fd);
	if (node->in_flag == 2)
		unlink(node->infile);
}

/*
** Handle output redirections: > or >>
**
** Files are pre-validated in parent process.
** Here we just open and redirect.
**
** Flags:
** - O_CREAT: create file if not exist
** - O_WRONLY: open for writing only
** - O_TRUNC: clear content for >
** - O_APPEND: write at end for >>
*/
static void	handle_output_redirect(t_node *node)
{
	int	fd;
	int	flags;

	if (node->out_flag == 0)
		return ;
	flags = O_CREAT | O_WRONLY;
	if (node->out_flag == 1)
		flags |= O_TRUNC;
	else if (node->out_flag == 2)
		flags |= O_APPEND;
	fd = open(node->outfile, flags, 0644);
	if (fd < 0)
	{
		ft_perror(NULL, node->outfile);
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

int	validate_infile(t_node *node)
{
	if (node->in_flag != 1)
		return (0);
	if (access(node->infile, F_OK) < 0)
		return (ft_file_error(DIR_ERR, node->infile, 1), 1);
	if (access(node->infile, R_OK) < 0)
		return (ft_file_error(PERM_ERR, node->infile, 1), 1);
	return (0);
}

int	validate_outfile(t_node *node)
{
	if (node->out_flag == 0)
		return (0);
	if (access(node->outfile, F_OK) == 0 && access(node->outfile, W_OK) < 0)
		return (ft_file_error(PERM_ERR, node->outfile, 1), 1);
	return (0);
}
