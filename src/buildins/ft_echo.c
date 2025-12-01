/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:21:49 by zmin              #+#    #+#             */
/*   Updated: 2025/12/01 19:44:03 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"
#include "utils.h"

// check if the second args start with -
// loop until all the n are gone
// after that check if it's the end or something else
// if there is something else, break
// if not, n_flag is valid and move to next args
static void	check_nflag(t_node *node, int *i, int *n_flag)
{
	int	j;

	while (node->full_cmd[*i] && node->full_cmd[*i][0] == '-')
	{
		j = 1;
		while (node->full_cmd[*i][j] == 'n')
			j++;
		if (node->full_cmd[*i][j] != '\0')
			break ;
		*n_flag = 1;
		(*i)++;
	}
}

int	ft_echo(t_node *node)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	check_nflag(node, &i, &n_flag);
	while (node->full_cmd[i])
	{
		printf("%s", node->full_cmd[i]);
		if (node->full_cmd[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
