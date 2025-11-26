/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 19:49:33 by zmin              #+#    #+#             */
/*   Updated: 2025/11/26 19:55:15 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"

int	exit_status(int mode, int value)
{
	static int	status;

	if (mode == 1)
		status = value;
	return (status);
}

void	set_exit_status(int value)
{
	exit_status(1, value);
}

int	get_exit_status(void)
{
	return (exit_status(0, 0));
}
