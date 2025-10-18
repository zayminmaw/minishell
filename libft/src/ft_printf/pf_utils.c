/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 22:32:02 by zmin              #+#    #+#             */
/*   Updated: 2025/09/10 22:56:05 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pf_putchar(int c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	pf_putstr(char *str)
{
	if (str == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}
