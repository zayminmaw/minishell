/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 23:39:58 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:37:02 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Concatenates two strings with size-bounded buffer.
** 
** Parameters:
**   s1 - First string to join (null-terminated)
**   s2 - Second string to join (null-terminated)
** 
** Return:
**   Returns a pointer to a newly allocated concatenated string,
**   or NULL if allocation fails.
** 
** Edge cases:
**   - Returns NULL if allocation fails
**   - Caller must free the returned string
**   - Undefined behavior if s1 or s2 is NULL (no null check)
**   - Allocates strlen(s1) + strlen(s2) + 1 bytes
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	char	*start;

	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	start = dest;
	while (*s1 != '\0')
	{
		*(dest++) = *(s1++);
	}
	while (*s2 != '\0')
		*(dest++) = *(s2++);
	*dest = '\0';
	return (start);
}
