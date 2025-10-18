/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:03:14 by zmin              #+#    #+#             */
/*   Updated: 2025/10/07 20:35:04 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_valid(int c, int baselen);
static void	get_char_value(char val, int *res);

int	ft_atoi_base(const char *str, int str_base)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && is_valid(str[i], str_base))
	{
		res *= str_base;
		get_char_value(str[i], &res);
		i++;
	}
	return (res * sign);
}

static void	get_char_value(char val, int *res)
{
	if (val >= '0' && val <= '9')
		*res += val - '0';
	else if (val >= 'a' && val <= 'f')
		*res += val - 'a' + 10;
	else if (val >= 'A' && val <= 'F')
		*res += val - 'A' + 10;
}

static int	is_valid(int ch, int baselen)
{
	char	*lcbase;
	char	*ucbase;
	int		i;

	lcbase = "0123456789abcdef";
	ucbase = "0123456789ABCDEF";
	i = 0;
	while (i < baselen)
	{
		if (ch == lcbase[i] || ch == ucbase[i])
			return (1);
		i++;
	}
	return (0);
}
