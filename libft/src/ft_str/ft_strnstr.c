/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:51:40 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:37:56 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Locates a substring in a string within a specified length.
** 
** Parameters:
**   big    - The string to search (null-terminated)
**   little - The substring to find (null-terminated)
**   len    - Maximum number of characters to search
** 
** Return:
**   Returns a pointer to the first occurrence of little in big,
**   or NULL if not found within len characters.
** 
** Edge cases:
**   - Returns big if little is empty string
**   - Returns NULL if little is not found within len characters
**   - Only searches within the first len bytes of big
**   - Stops search at null terminator even if len is larger
*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == 0)
		return ((char *) big);
	i = 0;
	j = 0;
	while (i < len && big[i])
	{
		while (big[i + j] && big[i + j] == little[j] && i + j < len)
		{
			j++;
			if (little[j] == 0)
				return ((char *) big + i);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
