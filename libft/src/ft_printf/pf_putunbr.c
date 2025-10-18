/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:38:08 by zmin              #+#    #+#             */
/*   Updated: 2025/09/10 22:55:58 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pf_putunbr(unsigned int n)
{
	int	count;

	count = 0;
	if (n < 10)
	{
		count += pf_putchar((n % 10) + '0');
		return (count);
	}
	count += pf_putunbr(n / 10);
	count += pf_putchar((n % 10) + '0');
	return (count);
}
