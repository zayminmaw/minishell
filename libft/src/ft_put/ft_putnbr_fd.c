/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:24:19 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:35:56 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Outputs an integer to the specified file descriptor.
** 
** Parameters:
**   n  - The integer to output
**   fd - The file descriptor to write to
** 
** Return:
**   None (void function)
** 
** Edge cases:
**   - Handles INT_MIN (-2147483648) correctly using long conversion
**   - Outputs '-' for negative numbers
**   - Uses recursion to output digits from left to right
**   - If fd is invalid, write will fail but function doesn't report error
*/
void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr = -nbr;
	}
	if (nbr >= 10)
		ft_putnbr_fd(nbr / 10, fd);
	nbr = nbr % 10 + 48;
	write(fd, &nbr, 1);
}
