/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_appendchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 21:41:49 by zmin              #+#    #+#             */
/*   Updated: 2025/11/12 21:47:14 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_appendchar(char *str, char c)
{
	char	*res;
	int		len;

	len = ft_strlen(str);
	res = malloc(sizeof(char) * len + 2);
	if (!res)
		return (NULL);
	ft_strlcpy(res, str, len + 1);
	res[len] = c;
	res[len + 1] = '\0';
	free(str);
	return (res);
}
