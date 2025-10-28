/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 23:17:03 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:38:18 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Extracts a substring from a string.
** 
** Parameters:
**   s     - The source string (null-terminated)
**   start - Starting index of substring
**   len   - Maximum length of substring
** 
** Return:
**   Returns a pointer to the newly allocated substring,
**   or NULL if allocation fails or s is NULL.
** 
** Edge cases:
**   - Returns NULL if s is NULL
**   - Returns empty string if start >= string length
**   - Adjusts len if it exceeds remaining string length
**   - Caller must free the returned string
**   - Returns NULL if malloc fails
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	str = malloc ((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
