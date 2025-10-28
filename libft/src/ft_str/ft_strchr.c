/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:38:41 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:36:37 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Locates the first occurrence of a character in a string.
** 
** Parameters:
**   s - The string to search (null-terminated)
**   c - The character to locate (as int, converted to char)
** 
** Return:
**   Returns a pointer to the first occurrence of c in s,
**   or NULL if c is not found.
** 
** Edge cases:
**   - Can find the null terminator ('\0')
**   - Returns pointer to '\0' if c is '\0'
**   - Returns NULL if character not found
**   - Searches entire string including the terminating null byte
*/
char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char) c;
	i = 0;
	while (s[i])
	{
		if (cc == s[i])
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (cc == s[i])
		return ((char *)&s[i]);
	return (NULL);
}
