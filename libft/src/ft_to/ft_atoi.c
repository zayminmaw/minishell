/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 21:24:57 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:39:06 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Converts a string to an integer.
** 
** Parameters:
**   nptr - The string to convert (null-terminated)
** 
** Return:
**   Returns the converted integer value.
** 
** Edge cases:
**   - Skips leading whitespace characters (9-13 and 32)
**   - Handles optional '+' sign (but not if followed by '-')
**   - Handles '-' sign for negative numbers
**   - Stops conversion at first non-digit character
**   - Does not check for overflow (undefined behavior for values > INT_MAX)
*/
int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	res;

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
/*
static int	ft_isspace(int c)
{
	if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 23)
		return (1);
	return (0);
}
*/
