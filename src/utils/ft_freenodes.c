/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freenodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:29:38 by zmin              #+#    #+#             */
/*   Updated: 2025/12/17 19:12:48 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_freenodes(t_node *nodes)
{
	int	i;
	int	len;

	len = nodes->env->node_len;
	i = 0;
	while (i < len)
	{
		if (nodes[i].full_cmd)
			ft_strarr_free(nodes[i].full_cmd);
		if (nodes[i].exec_path)
			free(nodes[i].exec_path);
		if (nodes[i].infiles)
			ft_strarr_free(nodes[i].infiles);
		if (nodes[i].outfiles)
			ft_strarr_free(nodes[i].outfiles);
		if (nodes[i].delimiters)
			ft_strarr_free(nodes[i].delimiters);
		i++;
	}
	free(nodes);
}
