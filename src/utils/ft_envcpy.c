/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:43:44 by zmin              #+#    #+#             */
/*   Updated: 2025/11/02 18:24:28 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// copy env (2D) and return new memory allocated 2D string
char	**ft_envcpy(char **envp)
{
	int		len;
	char	**envp_cpy;

	len = 0;
	while (envp[len])
		len++;
	envp_cpy = malloc(sizeof(char *) * (len + 1));
	envp_cpy[len] = NULL;
	len = 0;
	while (envp[len])
	{
		envp_cpy[len] = ft_strdup(envp[len]);
		len++;
	}
	return (envp_cpy);
}
