/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:14:01 by zmin              #+#    #+#             */
/*   Updated: 2025/09/10 22:55:54 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pf_puthex_long(unsigned long n);

int	pf_putptr(void *n)
{
	int				count;
	unsigned long	np;

	np = (unsigned long)n;
	count = 0;
	if (n == NULL || n == 0)
	{
		count += pf_putstr("(nil)");
		return (count);
	}
	count += pf_putstr("0x");
	count += pf_puthex_long(np);
	return (count);
}

int	pf_puthex_long(unsigned long n)
{
	int					count;
	unsigned long long	nll;

	count = 0;
	nll = (unsigned long long)n;
	if (nll >= 16)
	{
		count += pf_puthex_long(nll / 16);
		count += pf_puthex_long(nll % 16);
	}
	else
	{
		if (nll <= 9)
			count += pf_putchar(nll + '0');
		else
		{
			count += pf_putchar(nll - 10 + 'a');
		}
	}
	return (count);
}
