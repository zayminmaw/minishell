/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 13:45:42 by zmin              #+#    #+#             */
/*   Updated: 2025/11/25 20:08:21 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>

typedef struct s_env
{
	int			node_len;
	int			**fd;
	char		**envp;
	char		*homepath;
}				t_env;

typedef enum e_node_type
{
	ALIEN,
	CMD,
	BUILDIN_PARENT,
	BUILDIN_CHILD,
	PIPE,
	DOUBLE_AND,
	DOUBLE_OR,
	L_PAR,
	R_PAR
}				t_node_type;

// in_flag 0 = none, 1 = <, 2 = <<
// out_flag 0 = none, 1 = >, 2 = >>
typedef struct s_node
{
	t_node_type	node_type;
	char		*exec_path;
	char		**full_cmd;
	int			in_flag;
	int			out_flag;
	char		*infile;
	char		*outfile;
	char		*delimiter;
	int			cmd_count;
	int			real_cmd_count;
	t_env		*env;
}				t_node;

typedef enum e_parse_error
{
	QUOTE_ERR,
	SYN_ERR,
}				t_parse_error;

typedef enum e_file_error
{
	DIR_ERR,
	PERM_ERR,
	CMD_ERR,
	ISDIR_ERR,
	NOTDIR_ERR,
}				t_file_error;

typedef enum e_process_error
{
	DUP_ERR,
	FORK_ERR,
	PIPE_ERR,
	MEM_ERR,
}				t_process_error;

typedef enum e_env_error
{
	HOMESET_ERR,
	PWDSET_ERR,
}				t_env_error;

#endif