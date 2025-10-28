/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:24:32 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:31:23 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Checks if a character is alphanumeric.
** 
** Parameters:
**   c - The character to check (as int to handle EOF)
** 
** Return:
**   Returns the character value if it is alphanumeric (letter or digit),
**   0 otherwise.
** 
** Edge cases:
**   - Returns 0 for non-alphanumeric characters
**   - Returns 0 for control characters and special symbols
*/
int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
	{
		return (c);
	}
	return (0);
}
