/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freenodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmin-kha <wmin-kha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:29:38 by zmin              #+#    #+#             */
/*   Updated: 2025/12/17 02:50:36 by wmin-kha         ###   ########.fr       */
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
		if (nodes[i].infile)
			free(nodes[i].infile);
		if (nodes[i].outfile)
			free(nodes[i].outfile);
		if (nodes[i].delimiters)
			ft_strarr_free(nodes[i].delimiters);
		i++;
	}
	free(nodes);
}
