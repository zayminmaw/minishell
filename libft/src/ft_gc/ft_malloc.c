/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:28:42 by zmin              #+#    #+#             */
/*   Updated: 2025/10/02 20:13:40 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t size)
{
	t_list	**malloc_lst;
	t_list	*new_node;
	void	*new_malloc;

	malloc_lst = ft_malloc_lst();
	new_malloc = malloc(size);
	if (!new_malloc)
		return (NULL);
	new_node = ft_lstnew(new_malloc);
	if (!new_node)
	{
		free(new_malloc);
		return (NULL);
	}
	ft_lstadd_back(malloc_lst, new_node);
	return (new_malloc);
}
