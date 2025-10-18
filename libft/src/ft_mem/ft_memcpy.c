/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:01:27 by zmin              #+#    #+#             */
/*   Updated: 2025/08/27 22:57:28 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_tmp;
	unsigned char	*src_tmp;

	if (dest == NULL && src == NULL)
	{
		return (dest);
	}
	dest_tmp = (unsigned char *) dest;
	src_tmp = (unsigned char *) src;
	while (n > 0)
	{
		*(dest_tmp++) = *(src_tmp++);
		n--;
	}
	return (dest);
}
