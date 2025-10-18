/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:38:41 by zmin              #+#    #+#             */
/*   Updated: 2025/08/28 20:00:52 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char) c;
	i = 0;
	while (s[i])
	{
		if (cc == s[i])
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (cc == s[i])
		return ((char *)&s[i]);
	return (NULL);
}
