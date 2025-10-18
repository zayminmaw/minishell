/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:40:15 by zmin              #+#    #+#             */
/*   Updated: 2025/08/30 15:57:55 by zmin             ###   ########.fr       */
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
