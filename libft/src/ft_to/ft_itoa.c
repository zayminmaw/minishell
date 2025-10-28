/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:40:15 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:39:16 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	if (n == 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

/*
** Converts an integer to a string.
** 
** Parameters:
**   n - The integer to convert
** 
** Return:
**   Returns a newly allocated string representing the integer,
**   or NULL if allocation fails.
** 
** Edge cases:
**   - Handles negative numbers (adds '-' prefix)
**   - Handles zero correctly
**   - Handles INT_MIN (-2147483648) using long conversion
**   - Returns NULL if malloc fails
**   - Caller must free the returned string
**   - Helper function int_len calculates required string length
*/
char	*ft_itoa(int n)
{
	char	*res;
	int		len;
	long	nbr;

	nbr = n;
	len = int_len(nbr);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	if (nbr < 0)
	{
		res[0] = '-';
		nbr = -nbr;
	}
	res[len--] = '\0';
	if (nbr == 0)
		res[len] = '0';
	while (nbr != 0)
	{
		res[len] = ((nbr % 10) + 48);
		nbr = nbr / 10;
		len--;
	}
	return (res);
}
/*
#include <stdio.h>
 int  main(void)
 {
      char    *result;

      result = ft_itoa(-888);
      printf("->%s<-\n", result);
      printf("%d", int_len(-888));
      free(result);
      return (0);
 }
*/
