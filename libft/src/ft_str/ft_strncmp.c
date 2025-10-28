/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:47:47 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:37:48 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Compares up to n characters of two strings.
** 
** Parameters:
**   s1 - First string to compare (null-terminated)
**   s2 - Second string to compare (null-terminated)
**   n  - Maximum number of characters to compare
** 
** Return:
**   Returns 0 if strings are equal,
**   negative value if s1 < s2,
**   positive value if s1 > s2.
** 
** Edge cases:
**   - Returns 0 if n is 0
**   - Comparison stops at null terminator or after n characters
**   - Uses unsigned char for comparison
**   - Returns difference of first non-matching characters
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
