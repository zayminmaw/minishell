/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:43:03 by zmin              #+#    #+#             */
/*   Updated: 2025/09/10 22:55:32 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pf_puthex(unsigned int n, const char type)
{
	int	count;

	count = 0;
	if (n >= 16)
	{
		count += pf_puthex(n / 16, type);
		count += pf_puthex(n % 16, type);
	}
	else
	{
		if (n <= 9)
			count += pf_putchar(n + '0');
		else
		{
			if (type == 'x')
				count += pf_putchar(n - 10 + 'a');
			if (type == 'X')
				count += pf_putchar(n - 10 + 'A');
		}
	}
	return (count);
}
