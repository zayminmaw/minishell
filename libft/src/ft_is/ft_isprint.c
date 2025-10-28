/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:33:40 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:32:01 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Checks if a character is printable.
** 
** Parameters:
**   c - The character to check (as int to handle EOF)
** 
** Return:
**   Returns the character value if it is printable (ASCII 32-126),
**   0 otherwise.
** 
** Edge cases:
**   - Returns 0 for control characters (< 32)
**   - Returns 0 for DEL character (127) and beyond
**   - Includes space character (32) as printable
*/
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
	{
		return (c);
	}
	return (0);
}
