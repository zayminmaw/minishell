/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmin <zmin@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:28:42 by zmin              #+#    #+#             */
/*   Updated: 2025/10/28 19:30:21 by zmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates memory and tracks it for garbage collection.
** 
** Parameters:
**   size - Number of bytes to allocate
** 
** Return:
**   Returns a pointer to the allocated memory,
**   or NULL if allocation fails.
** 
** Edge cases:
**   - Returns NULL if malloc fails
**   - Adds allocation to tracked list for later cleanup
**   - Uses ft_malloc_lst to get the tracking list
**   - Uses ft_lstnew to create tracking node
**   - Uses ft_lstadd_back to add to tracking list
**   - Memory can be freed all at once with ft_malloc_clear
*/
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
