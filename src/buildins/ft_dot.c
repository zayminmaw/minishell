/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dot.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 01:35:00 by wmin-kha          #+#    #+#             */
/*   Updated: 2025/12/24 01:35:00 by wmin-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"
#include "exit_status.h"
#include "minishell.h"
#include "utils.h"
#include <unistd.h>

int	ft_dot(t_node *node)
{
	if (!node->full_cmd[1])
	{
		write(2, "minishell: .: filename argument required\n", 42);
		write(2, ".: usage: . filename [arguments]\n", 33);
		set_exit_status(2);
		return (0);
	}
	write(2, "minishell: .: not implemented\n", 30);
	set_exit_status(1);
	return (0);
}
