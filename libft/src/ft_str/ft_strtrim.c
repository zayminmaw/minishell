/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 18:26:16 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:38:08 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Trims characters from the beginning and end of a string.
** 
** Parameters:
**   s1  - The string to trim (null-terminated)
**   set - Set of characters to remove from both ends
** 
** Return:
**   Returns a pointer to a newly allocated trimmed string,
**   or NULL if allocation fails.
** 
** Edge cases:
**   - Returns empty string if s1 is empty
**   - Caller must free the returned string
**   - Uses ft_strchr to check if character is in set
**   - Uses ft_substr to create the trimmed substring
**   - Trims from both beginning and end
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(s1) - 1;
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[i]))
		i++;
	while (ft_strrchr(set, s1[j]))
		j--;
	return (ft_substr(s1, i, j - (i - 1)));
}
