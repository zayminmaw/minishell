/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isenvempty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 21:10:43 by zmin              #+#    #+#             */
/*   Updated: 2025/10/30 21:35:03 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// Return 1 if empty and 0 if not empty
int	ft_isenvempty(char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i == 0);
}
