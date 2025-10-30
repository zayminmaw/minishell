/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 13:45:42 by zmin              #+#    #+#             */
/*   Updated: 2025/10/30 21:41:09 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>

int			g_status;

typedef struct s_env
{
	int		px_len;
	int		**fd;
	char	**envp;
	char	*homepath;
}			t_env;

#endif