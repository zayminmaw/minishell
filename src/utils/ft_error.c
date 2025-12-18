/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 14:23:00 by zmin              #+#    #+#             */
/*   Updated: 2025/12/18 18:20:14 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"
#include "utils.h"

void	print_error(char *prefix, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	if (prefix)
		ft_putstr_fd(prefix, 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	ft_putstr_fd("\n", 2);
}

void	*ft_syntax_error(t_parse_error err_type, int exit_err_no)
{
	set_exit_status(exit_err_no);
	if (err_type == QUOTE_ERR)
		print_error("error while looking for matching quote", NULL);
	else if (err_type == SYN_ERR)
		print_error("syntax error near unexpected token", NULL);
	return (NULL);
}

void	*ft_env_error(t_env_error err_type, char *msg, int exit_err_no)
{
	set_exit_status(exit_err_no);
	if (err_type == HOMESET_ERR)
		print_error(msg, " HOME not set");
	else if (err_type == PWDSET_ERR)
		print_error(msg, " OLDPWD not set");
	return (NULL);
}

void	*ft_process_error(t_process_error err_type, int exit_err_no)
{
	set_exit_status(exit_err_no);
	if (err_type == DUP_ERR)
		print_error("dup2 failed", NULL);
	else if (err_type == FORK_ERR)
		print_error("fork failed", NULL);
	else if (err_type == PIPE_ERR)
		print_error("error creating pipe", NULL);
	else if (err_type == MEM_ERR)
		print_error("memory allocation failed", NULL);
	return (NULL);
}

void	*ft_file_error(t_file_error err_type, char *msg, int exit_err_no)
{
	set_exit_status(exit_err_no);
	if (err_type == DIR_ERR)
		print_error(msg, " No such file or directory");
	else if (err_type == PERM_ERR)
		print_error(msg, " permission denied");
	else if (err_type == CMD_ERR)
		print_error(msg, " command not found");
	else if (err_type == ISDIR_ERR)
		print_error(msg, " is a directory");
	else if (err_type == NOTDIR_ERR)
		print_error(msg, " not a directory");
	return (NULL);
}

void	ft_perror(char *prefix, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	if (prefix)
	{
		ft_putstr_fd(prefix, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	ft_putstr_fd("\n", 2);
}
