/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 01:03:36 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:39:25 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Converts an uppercase letter to lowercase.
** 
** Parameters:
**   c - The character to convert (as int to handle EOF)
** 
** Return:
**   Returns the lowercase equivalent if c is uppercase (A-Z),
**   otherwise returns c unchanged.
** 
** Edge cases:
**   - Only converts ASCII uppercase letters (65-90)
**   - Returns character unchanged if not uppercase
**   - Does not affect digits or special characters
*/
int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		return (c + 32);
	}
	return (c);
}
