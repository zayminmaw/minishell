/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:30:41 by zmin              #+#    #+#             */
/*   Updated: 2025/08/27 23:09:27 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_tmp;
	unsigned char	*src_tmp;
	size_t			i;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest_tmp = (unsigned char *) dest;
	src_tmp = (unsigned char *) src;
	i = 0;
	if (src_tmp < dest_tmp)
	{
		while (n-- > 0)
			dest_tmp[n] = src_tmp[n];
	}
	else
	{
		while (i < n)
		{
			dest_tmp[i] = src_tmp[i];
			i++;
		}
	}
	return (dest);
}
