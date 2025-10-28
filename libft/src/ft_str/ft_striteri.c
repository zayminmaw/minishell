/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:02:31 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:36:54 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Applies a function to each character of a string with its index.
** 
** Parameters:
**   s - The string to iterate (null-terminated)
**   f - Function to apply (takes index and pointer to character)
** 
** Return:
**   None (void function)
** 
** Edge cases:
**   - Undefined behavior if s is NULL (no null check)
**   - Function f can modify characters in-place
**   - f is called with index and address of each character
**   - Undefined behavior if f is NULL
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
