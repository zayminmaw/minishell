/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:44:34 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:35:17 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Formatted output function similar to standard printf.
** 
** Parameters:
**   format - Format string with conversion specifiers
**   ...    - Variable arguments based on format specifiers
** 
** Return:
**   Returns the number of characters printed.
** 
** Edge cases:
**   - Supports: %c (char), %s (string), %d/%i (int), %u (unsigned int)
**   - Supports: %x/%X (hex), %p (pointer), %% (literal %)
**   - Uses pf_format_str to handle different format types
**   - Returns count of characters written to stdout
*/
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
