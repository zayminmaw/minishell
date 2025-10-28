/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 16:44:43 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:37:40 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Creates a new string by applying a function to each character.
** 
** Parameters:
**   s - The string to transform (null-terminated)
**   f - Function to apply (takes index and character, returns new character)
** 
** Return:
**   Returns a pointer to the newly allocated transformed string,
**   or NULL if allocation fails.
** 
** Edge cases:
**   - Returns NULL if malloc fails
**   - Caller must free the returned string
**   - Undefined behavior if s or f is NULL (no null check)
**   - f is called with index and value of each character
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*dest;

	len = ft_strlen(s);
	i = 0;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = f(i, s[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
