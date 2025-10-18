/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:16:24 by zmin              #+#    #+#             */
/*   Updated: 2025/08/27 20:24:09 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*tmp;

	tmp = (unsigned char *) s;
	while (n > 0)
	{
		*(tmp++) = (unsigned char) c;
		n--;
	}
	return (s);
}
