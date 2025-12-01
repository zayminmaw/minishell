/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:46:05 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/01 02:00:16 by wmin-kha         ###   ########.fr       */
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

	if (node->in_flag != 1)
		return ;
	fd = open(node->infile, O_RDONLY);
	if (dup2(fd, STDIN_FILENO) < 0)
		ft_process_error(DUP_ERR, 1);
	close(fd);
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
	if (dup2(fd, STDOUT_FILENO) < 0)
		ft_process_error(DUP_ERR, 1);
	close(fd);
}

void	handle_redirections(t_node *node)
{
	handle_input_redirect(node);
	handle_output_redirect(node);
}
