/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:33:51 by zmin              #+#    #+#             */
/*   Updated: 2025/09/10 22:55:50 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pf_putnbr(int nbr)
{
	char	*s_nbr;
	int		count;

	s_nbr = ft_itoa(nbr);
	count = pf_putstr(s_nbr);
	free(s_nbr);
	return (count);
}
