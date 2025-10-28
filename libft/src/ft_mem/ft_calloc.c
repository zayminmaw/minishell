/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 22:36:26 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:40:39 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates and zeros memory for an array.
** 
** Parameters:
**   nmemb - Number of elements to allocate
**   size  - Size of each element in bytes
** 
** Return:
**   Returns a pointer to the allocated and zeroed memory,
**   or NULL if allocation fails or overflow would occur.
** 
** Edge cases:
**   - Returns malloc(0) if either nmemb or size is 0
**   - Returns NULL if multiplication would overflow INT_MAX
**   - Returns NULL if allocation fails
**   - Memory is initialized to zero (unlike malloc)
*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*tmp;
	size_t			i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb * size > INT_MAX || nmemb > INT_MAX || size > INT_MAX)
		return (NULL);
	i = 0;
	tmp = malloc(nmemb * size);
	if (!tmp)
		return (NULL);
	while (i < nmemb * size)
	{
		tmp[i] = 0;
		i++;
	}
	return ((void *)tmp);
}
