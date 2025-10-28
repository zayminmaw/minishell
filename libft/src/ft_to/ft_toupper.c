/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 00:59:26 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:39:33 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Converts a lowercase letter to uppercase.
** 
** Parameters:
**   c - The character to convert (as int to handle EOF)
** 
** Return:
**   Returns the uppercase equivalent if c is lowercase (a-z),
**   otherwise returns c unchanged.
** 
** Edge cases:
**   - Only converts ASCII lowercase letters (97-122)
**   - Returns character unchanged if not lowercase
**   - Does not affect digits or special characters
*/
int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}
