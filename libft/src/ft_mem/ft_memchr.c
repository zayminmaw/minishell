/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:27:06 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:34:04 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Searches for a byte in a memory block.
** 
** Parameters:
**   s - Pointer to the memory area to search
**   c - Byte value to search for (as int, but used as unsigned char)
**   n - Number of bytes to search
** 
** Return:
**   Returns a pointer to the first occurrence of the byte c,
**   or NULL if the byte is not found within n bytes.
** 
** Edge cases:
**   - Returns NULL if the byte is not found in the first n bytes
**   - Can find '\0' bytes unlike string functions
**   - The comparison is done using unsigned char
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	cc;
	unsigned char	*str;

	i = 0;
	cc = (unsigned char) c;
	str = (unsigned char *) s;
	while (i < n)
	{
		if (str[i] == cc)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}
