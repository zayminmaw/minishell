/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:59:42 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/10 21:31:54 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"
#include "exit_status.h"
#include "minishell.h"
#include "utils.h"
#include <unistd.h>

static int	cd_error(t_cd_error type, const char *path)
{
	if (type == PATH && path)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	else if (type == HOME_NOT_SET)
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	else if (type == OLDPWD)
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
	else if (type == TOO_MANY)
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	set_exit_status(1);
	return (1);
}

static int	cd_change_dir(t_env *env, const char *target, int print_new)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = ft_getenv(env, "PWD");
	if (old_pwd)
		old_pwd = ft_strdup(old_pwd);
	else
		old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (set_exit_status(1), 1);
	if (chdir(target) == -1)
		return (free(old_pwd), cd_error(PATH, target));
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (free(old_pwd), set_exit_status(1), 1);
	// TODO:
	if (print_new)
		ft_putendl_fd(new_pwd, 1);
	return (free(old_pwd), free(new_pwd), set_exit_status(0), 0);
}

char	**ft_cd(t_node *node)
{
}
