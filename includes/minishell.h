/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 13:45:42 by zmin              #+#    #+#             */
/*   Updated: 2025/11/02 15:26:17 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>

typedef struct s_env
{
	int		px_len;
	int		**fd;
	char	**envp;
	char	*homepath;
}			t_env;

typedef enum e_parse_error
{
	QUOTE_ERR,
	SYN_ERR,
}			t_parse_error;

typedef enum e_file_error
{
	DIR_ERR,
	PERM_ERR,
	CMD_ERR,
	ISDIR_ERR,
	NOTDIR_ERR,
}			t_file_error;

typedef enum e_process_error
{
	DUP_ERR,
	FORK_ERR,
	PIPE_ERR,
	MEM_ERR,
}			t_process_error;

typedef enum e_env_error
{
	HOMESET_ERR,
	PWDSET_ERR,
}			t_env_error;

#endif