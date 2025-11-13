/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 14:23:00 by zmin              #+#    #+#             */
/*   Updated: 2025/11/13 21:30:22 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globals.h"
#include "utils.h"

void	*ft_syntax_error(t_parse_error err_type, int exit_err_no)
{
	g_status = exit_err_no;
	if (err_type == QUOTE_ERR)
		printf("minishell: error while looking for matching quote\n");
	else if (err_type == SYN_ERR)
		printf("minishell: syntax error near unexpected token\n");
	return (NULL);
}

void	*ft_env_error(t_env_error err_type, char *msg, int exit_err_no)
{
	g_status = exit_err_no;
	if (err_type == HOMESET_ERR)
		printf("minishell: %s HOME not set\n", msg);
	else if (err_type == PWDSET_ERR)
		printf("minishell: %s OLDPWD not set\n", msg);
	return (NULL);
}

void	*ft_process_error(t_process_error err_type, int exit_err_no)
{
	g_status = exit_err_no;
	if (err_type == DUP_ERR)
		printf("minishell: dup2 failed\n");
	else if (err_type == FORK_ERR)
		printf("minishell: fork failed\n");
	else if (err_type == PIPE_ERR)
		printf("minishell: error creating pipe\n");
	else if (err_type == MEM_ERR)
		printf("minishell: memory allocation failed\n");
	return (NULL);
}

void	*ft_file_error(t_file_error err_type, char *msg, int exit_err_no)
{
	g_status = exit_err_no;
	if (err_type == DIR_ERR)
		printf("minishell: no such file or directory: %s\n", msg);
	else if (err_type == PERM_ERR)
		printf("minishell: permission denied: %s\n", msg);
	else if (err_type == CMD_ERR)
		printf("minishell: command not found: %s\n", msg);
	else if (err_type == ISDIR_ERR)
		printf("minishell: is a directory: %s\n", msg);
	else if (err_type == NOTDIR_ERR)
		printf("minishell: not a directory: %s\n", msg);
	return (NULL);
}
