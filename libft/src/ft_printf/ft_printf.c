/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:44:34 by zmin              #+#    #+#             */
/*   Updated: 2025/09/10 22:59:20 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	args;
	int		count;

	count = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += pf_format_str(args, format[i]);
		}
		else
			count += pf_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
