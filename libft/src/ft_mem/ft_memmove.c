/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:30:41 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:34:31 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Copies n bytes from src to dest, handling overlapping regions safely.
** 
** Parameters:
**   dest - Pointer to the destination memory block
**   src  - Pointer to the source memory block
**   n    - Number of bytes to copy
** 
** Return:
**   Returns the original dest pointer, or NULL if both are NULL.
** 
** Edge cases:
**   - Returns NULL if both dest and src are NULL
**   - Safely handles overlapping memory regions by copying backwards if needed
**   - If src < dest, copies from end to beginning to avoid corruption
**   - If dest <= src, copies from beginning to end
*/
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
