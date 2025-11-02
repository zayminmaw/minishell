/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 13:46:25 by zmin              #+#    #+#             */
/*   Updated: 2025/11/02 19:02:56 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globals.h"
#include "minishell.h"
#include "utils.h"

int	g_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argv;
	if (ft_isenvempty(envp))
		return (printf("Invalid env\n"), -1);
	if (argc != 1)
		return (printf("Invalid arguments\n"), -2);
	env = malloc(sizeof(t_env));
	if (!env)
		return (ft_process_error(MEM_ERR, 2), 2);
	env->envp = ft_envcpy(envp);
	env->envp = ft_delvar(env->envp, "_");
	env->envp = ft_addvar(env->envp, "_=/usr/bin/env");
	env->envp = ft_delvar(env->envp, "OLDPWD");
	env->homepath = getenv("HOME");
	if (!env->homepath)
		return (printf("Invalid home\n"), -1);
	ft_strarr_free(env->envp);
	free(env);
	return (g_status);
}
