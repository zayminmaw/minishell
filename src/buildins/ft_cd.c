/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:59:42 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/11 19:17:51 by wmin-kha         ###   ########.fr       */
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

static char	**cd_change_dir(char **env, const char *target, int print_new)
{
	char	*old_pwd;
	char	*cur_pwd;
	char	*new_pwd;

	cur_pwd = ft_getenv(env, "PWD");
	if (cur_pwd)
		old_pwd = ft_strdup(cur_pwd);
	else
		old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (set_exit_status(1), env);
	if (chdir(target) == -1)
	{
		free(old_pwd);
		cd_error(PATH, target);
		set_exit_status(1);
		return (env);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		free(old_pwd);
		set_exit_status(1);
		return (env);
	}
	env = cd_setenv_value(env, "OLDPWD", old_pwd);
	env = cd_setenv_value(env, "PWD", new_pwd);
	if (print_new)
		ft_putendl_fd(new_pwd, 1);
	free(old_pwd);
	free(new_pwd);
	set_exit_status(0);
	return (env);
}

static char	**cd_no_arg(char **env)
{
	char	*home;

	home = cd_getenv_value(env, "HOME");
	if (!home)
	{
		cd_error(HOME_NOT_SET, NULL);
		return (env);
	}
	return (cd_change_dir(env, home, 0));
}

static char	**cd_dash(char **env)
{
	char	*oldpwd;

	oldpwd = cd_getenv_value(env, "OLDPWD");
	if (!oldpwd)
	{
		cd_error(OLDPWD, NULL);
		return (env);
	}
	return (cd_change_dir(env, oldpwd, 1));
}

char	**ft_cd(char **env, char **full_cmd)
{
	int	argc;

	argc = 0;
	while (full_cmd[argc])
		argc++;
	if (argc > 2)
	{
		cd_error(TOO_MANY, NULL);
		return (env);
	}
	if (argc == 1)
		return (cd_no_arg(env));
	if (ft_strcmp(full_cmd[1], "-") == 0)
		return (cd_dash(env));
	return (cd_change_dir(env, full_cmd[1], 0));
}
