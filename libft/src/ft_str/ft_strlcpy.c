/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 23:25:59 by zmin              #+#    #+#             */
/*   Updated: 2025/08/28 00:06:30 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size > src_len + 1)
		ft_memcpy(dst, src, src_len + 1);
	else if (size != 0)
	{
		ft_memcpy(dst, src, size - 1);
		dst[size - 1] = 0;
	}
	return (src_len);
}
