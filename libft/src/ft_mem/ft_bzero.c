/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:26:33 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:33:45 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Sets a block of memory to zero.
** 
** Parameters:
**   s - Pointer to the memory area to zero out
**   n - Number of bytes to set to zero
** 
** Return:
**   None (void function)
** 
** Edge cases:
**   - If n is 0, no bytes are modified
**   - Undefined behavior if s is NULL (standard bzero behavior)
**   - Commonly used to clear sensitive data or initialize structures
*/
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tmp_pt;

	tmp_pt = (unsigned char *) s;
	while (n > 0)
	{
		*(tmp_pt++) = '\0';
		n--;
	}
}
