/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 23:25:59 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:37:26 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Copies src to dst with size-bounded buffer, ensuring null-termination.
** 
** Parameters:
**   dst  - Destination buffer
**   src  - Source string to copy (null-terminated)
**   size - Size of destination buffer
** 
** Return:
**   Returns the length of src (for truncation detection).
** 
** Edge cases:
**   - Always null-terminates dst (if size > 0)
**   - Returns src length regardless of whether truncation occurred
**   - If size is 0, dst is not modified
**   - Safer alternative to strcpy
**   - Copies at most size-1 characters
*/
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
