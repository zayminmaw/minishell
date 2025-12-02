/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:36:13 by zmin              #+#    #+#             */
/*   Updated: 2025/12/02 20:18:07 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"
#include "exit_status.h"
#include "utils.h"

static int	validate_arg(const char *s, long *out)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	*out = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if (s[i] < '0' || s[i] > '9')
		return (-1);
	while (s[i] >= '0' && s[i] <= '9')
	{
		*out = *out * 10 + (s[i] - '0');
		i++;
	}
	if (s[i] != '\0')
		return (-1);
	*out *= sign;
	return (0);
}

// return 1 on exit and 0 on not exit
int	ft_exit(t_node *node)
{
	long	n;

	printf("exit\n");
	if (!node->full_cmd[1])
	{
		set_exit_status(0);
		return (1);
	}
	if (validate_arg(node->full_cmd[1], &n) < 0)
	{
		printf("minishell: exit: %s: numeric argument required\n",
			node->full_cmd[1]);
		set_exit_status(2);
		return (1);
	}
	if (node->full_cmd[2])
	{
		printf("minishell: exit: too many arguments\n");
		set_exit_status(1);
		return (0);
	}
	set_exit_status(n % 256);
	return (1);
}
