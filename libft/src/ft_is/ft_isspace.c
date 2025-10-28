/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:04:51 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:32:10 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Checks if a character is a whitespace character.
** 
** Parameters:
**   c - The character to check (as int to handle EOF)
** 
** Return:
**   Returns 1 if the character is a whitespace character,
**   0 otherwise.
** 
** Edge cases:
**   - Checks for: tab (9), newline (10), vertical tab (11),
**     form feed (12), carriage return (13), and space (32)
**   - Returns 0 for all other characters
*/
int	ft_isspace(int c)
{
	if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32)
		return (1);
	return (0);
}
