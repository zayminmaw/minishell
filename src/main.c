/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 13:46:25 by zmin              #+#    #+#             */
/*   Updated: 2025/11/02 15:30:08 by zmin             ###   ########.fr       */
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
	ft_strarr_free(env->envp);
	free(env);
	return (g_status);
}
