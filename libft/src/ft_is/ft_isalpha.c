/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:11:25 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:31:34 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Checks if a character is alphabetic.
** 
** Parameters:
**   c - The character to check (as int to handle EOF)
** 
** Return:
**   Returns the character value if it is a letter (A-Z or a-z),
**   0 otherwise.
** 
** Edge cases:
**   - Returns 0 for digits and special characters
**   - Only checks ASCII letters (65-90 for uppercase, 97-122 for lowercase)
*/
int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (c);
	}
	return (0);
}
