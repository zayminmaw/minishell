/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:31:13 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:38:01 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Locates the last occurrence of a character in a string.
** 
** Parameters:
**   s - The string to search (null-terminated)
**   c - The character to locate (as int, converted to char)
** 
** Return:
**   Returns a pointer to the last occurrence of c in s,
**   or NULL if c is not found.
** 
** Edge cases:
**   - Can find the null terminator ('\0')
**   - Returns pointer to '\0' if c is '\0'
**   - Returns NULL if character not found
**   - Searches entire string including the terminating null byte
*/
char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			cc;
	char			*res;

	cc = (char) c;
	i = 0;
	res = NULL;
	while (s[i])
	{
		if (cc == s[i])
			res = (char *) &s[i];
		i++;
	}
	if (s[i] == cc)
		res = (char *) &s[i];
	return (res);
}
