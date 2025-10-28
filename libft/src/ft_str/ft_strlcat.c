/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 00:27:57 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:37:11 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Appends src to dst with size-bounded buffer, ensuring null-termination.
** 
** Parameters:
**   dst  - Destination string buffer
**   src  - Source string to append (null-terminated)
**   size - Total size of destination buffer
** 
** Return:
**   Returns the total length of the string it tried to create
**   (initial dst length + src length).
** 
** Edge cases:
**   - Always null-terminates dst (if size > 0)
**   - Returns dst_len + src_len for length calculation
**   - If size <= dst_len, returns size + src_len
**   - If dst_len >= size, no concatenation occurs
**   - Safer alternative to strcat
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_len >= size)
		dst_len = size;
	if (dst_len == size)
		return (dst_len + src_len);
	if (src_len < size - dst_len)
	{
		ft_memcpy(dst + dst_len, src, src_len + 1);
	}
	else
	{
		ft_memcpy(dst + dst_len, src, size - dst_len - 1);
		dst[size - 1] = 0;
	}
	return (dst_len + src_len);
}
