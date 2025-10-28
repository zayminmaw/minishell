/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:40:15 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:39:02 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Converts a string to a long integer.
** 
** Parameters:
**   nptr - The string to convert (null-terminated)
** 
** Return:
**   Returns the converted long integer value.
** 
** Edge cases:
**   - Skips leading whitespace characters (9-13 and 32)
**   - Handles optional '+' sign (but not if followed by '-')
**   - Handles '-' sign for negative numbers
**   - Stops conversion at first non-digit character
**   - Returns long type for larger range than ft_atoi
*/
long	ft_atol(const char *nptr)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' && nptr[i + 1] != '-')
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (nptr[i] && nptr[i] >= 48 && nptr[i] <= 57)
	{
		res *= 10;
		res += nptr[i] - 48;
		i++;
	}
	res *= sign;
	return (res);
}
