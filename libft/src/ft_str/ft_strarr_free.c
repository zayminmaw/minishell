/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:05:55 by zmin              #+#    #+#             */
/*   Updated: 2025/09/14 20:12:14 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strarr_free(char **str_arr)
{
	int	i;

	i = 0;
	if (!str_arr)
		return ;
	while (str_arr[i])
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}
