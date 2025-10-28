/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:19:58 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:35:48 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Outputs a string followed by a newline to the specified file descriptor.
** 
** Parameters:
**   s  - The string to output (null-terminated)
**   fd - The file descriptor to write to
** 
** Return:
**   None (void function)
** 
** Edge cases:
**   - Undefined behavior if s is NULL (no null check)
**   - Always outputs a newline after the string
**   - If fd is invalid, write will fail but function doesn't report error
*/
void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
