/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:01:27 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:34:23 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Copies n bytes from src to dest.
** 
** Parameters:
**   dest - Pointer to the destination memory block
**   src  - Pointer to the source memory block
**   n    - Number of bytes to copy
** 
** Return:
**   Returns the original dest pointer.
** 
** Edge cases:
**   - Returns dest if both dest and src are NULL
**   - Undefined behavior if memory regions overlap (use ft_memmove instead)
**   - Can copy blocks containing null bytes
**   - If n is 0, nothing is copied
*/
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
