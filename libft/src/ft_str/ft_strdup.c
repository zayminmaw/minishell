/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 22:47:18 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:36:43 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Duplicates a string by allocating memory and copying content.
** 
** Parameters:
**   s - The string to duplicate (null-terminated)
** 
** Return:
**   Returns a pointer to the newly allocated duplicate string,
**   or NULL if allocation fails.
** 
** Edge cases:
**   - Returns NULL if malloc fails
**   - Caller must free the returned string
**   - Allocates exactly strlen(s) + 1 bytes
**   - Undefined behavior if s is NULL (no null check)
*/
char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	i;

	dest = malloc(ft_strlen(s) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
