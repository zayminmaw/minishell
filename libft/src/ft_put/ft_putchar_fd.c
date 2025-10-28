/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:13:53 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:35:41 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Outputs a character to the specified file descriptor.
** 
** Parameters:
**   c  - The character to output
**   fd - The file descriptor to write to
** 
** Return:
**   None (void function)
** 
** Edge cases:
**   - If fd is invalid, write will fail but function doesn't report error
**   - Common fd values: 0 (stdin), 1 (stdout), 2 (stderr)
*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
