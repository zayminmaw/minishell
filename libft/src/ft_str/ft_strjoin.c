/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 23:39:58 by zmin              #+#    #+#             */
/*   Updated: 2025/08/28 23:57:49 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	char	*start;

	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	start = dest;
	while (*s1 != '\0')
	{
		*(dest++) = *(s1++);
	}
	while (*s2 != '\0')
		*(dest++) = *(s2++);
	*dest = '\0';
	return (start);
}
