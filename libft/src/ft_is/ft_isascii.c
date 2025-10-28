/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:28:02 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:31:42 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Checks if a character is in the ASCII character set.
** 
** Parameters:
**   c - The character to check (as int)
** 
** Return:
**   Returns 1 if the character is within ASCII range (0-127),
**   0 otherwise.
** 
** Edge cases:
**   - Returns 0 for values outside the ASCII range (> 127 or < 0)
**   - Includes all control characters and printable ASCII characters
*/
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	return (0);
}
