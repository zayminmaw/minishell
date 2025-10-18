/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:51:40 by zmin              #+#    #+#             */
/*   Updated: 2025/08/28 21:10:34 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == 0)
		return ((char *) big);
	i = 0;
	j = 0;
	while (i < len && big[i])
	{
		while (big[i + j] && big[i + j] == little[j] && i + j < len)
		{
			j++;
			if (little[j] == 0)
				return ((char *) big + i);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
