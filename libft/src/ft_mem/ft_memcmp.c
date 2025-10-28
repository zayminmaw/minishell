/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:43:39 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:34:13 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Compares two memory blocks byte by byte.
** 
** Parameters:
**   s1 - Pointer to the first memory block
**   s2 - Pointer to the second memory block
**   n  - Number of bytes to compare
** 
** Return:
**   Returns 0 if the blocks are equal,
**   a negative value if s1 is less than s2,
**   a positive value if s1 is greater than s2.
** 
** Edge cases:
**   - Returns 0 if n is 0 (no comparison needed)
**   - Comparison is done using unsigned char values
**   - Can compare blocks containing null bytes
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
