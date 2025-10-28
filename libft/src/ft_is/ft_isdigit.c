/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:19:19 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:31:49 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Checks if a character is a decimal digit.
** 
** Parameters:
**   c - The character to check (as int to handle EOF)
** 
** Return:
**   Returns the character value if it is a digit (0-9),
**   0 otherwise.
** 
** Edge cases:
**   - Returns 0 for letters and special characters
**   - Only checks ASCII digits (48-57 corresponding to '0'-'9')
*/
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (c);
	}
	return (0);
}
