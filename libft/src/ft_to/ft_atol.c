/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:40:15 by zmin              #+#    #+#             */
/*   Updated: 2025/09/14 21:50:51 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
